test( binary_decode, pointer ) {

  given("an example struct with a pointer type");
    struct example {
      char* name;
      struct point {
        i32 x;
        i32 y;
      } *vertex;
      struct array* coordinates;
    } example;


  when("it has an associated schema that enforces a minimum length")
    struct reflect schema = {
      type(STRUCT, { sizeof(struct example), 3 }) {
        { field(name, struct example), type(POINTER, { 32 })
          {{ type(CHAR) }}
        },

        { field(vertex, struct example), type(POINTER, { 0 })
          {{ type(STRUCT, { sizeof(struct point), 2 }) {
            { field(x, struct point), type(I32) },
            { field(y, struct point), type(I32) }, }
          }}
        },

        { field(coordinates, struct example), type(POINTER, { 0 })
          {{ type(ARRAY, { 2, 2 }) {{ type(I32) }} }}
        },
      }
    };


  when("some input data is ready to decode");
    byte input[] = {
      0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* name size */
      0x54, 0x72, 0x69, 0x61, 0x6e, 0x67, 0x6c, 0x65,       /* name */
      0x21, 0x21, 0x00,

      0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* vertex size */
      0x04, 0x00, 0x00, 0x00,                               /* vertex->x */
      0x05, 0x00, 0x00, 0x00,                               /* vertex->y */

      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* coordinates length */
      0x07, 0x00, 0x00, 0x00,                               /* coordinates.1 */
      0x08, 0x00, 0x00, 0x00,                               /* coordinates.2 */
    };


  when("a protocol decoder is set up on this data");
    struct memory allocator = memory_init(4096);
    struct protocol decoder = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(input, sizeof(input)),
      .output = &io_writer(&example, sizeof(example)),
    };


  calling("binary_decode()");
    binary_decode(&decoder);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(io_exhausted(decoder.input) == true);

    verify(streq(example.name, "Triangle!!"));
    verify((void*) example.name == (void*) allocator.data);

    struct point* vertex = example.vertex;
    verify((void*) example.vertex == (void*) (allocator.data + 11));
    verify(vertex->x == 4);
    verify(vertex->y == 5);

    struct array* coordinates = example.coordinates;
    verify((void*) example.coordinates == (void*) (allocator.data + 11 + 8));
    verify(as(i32, array_get(coordinates, 0)) == 7);
    verify(as(i32, array_get(coordinates, 1)) == 8);

    /* The total allocations must be: 3 (pointers) and 1 (array data). */
    verify(allocator.allocations == 3 + 1);

  success();
    memory_release(&allocator);
}
