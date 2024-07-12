test( binary_decode, pointer ) {

  given("an example struct with a pointer type");
    struct example {
      char* name;
      struct point {
        i32 x;
        i32 y;
      } *vertex;
    } example;


  when("it has an associated schema that enforces a minimum length")
    struct reflect schema = {
      type(STRUCT, { sizeof(struct example), 2 }) {
        { field(name, struct example), type(POINTER, { 32 })
          {{ type(CHAR) }}
        },

        { field(vertex, struct example), type(POINTER, { 0 })
          {{ type(STRUCT, { sizeof(struct point), 2 }) {
            { field(x, struct point), type(I32) },
            { field(y, struct point), type(I32) }, }
          }}
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
    };


  when("a protocol decoder is set up on this data");
    struct memory allocator = memory_init(4096);
    struct protocol decoder = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(input, sizeof(input)),
      .output = &io_writer(&example, sizeof(example)),
      .error = &(struct failure) { 0 }
    };


  calling("binary_decode()");
    binary_decode(&decoder);


  must("decode the input data on the struct correctly");
    verify(decoder.error->occurred == false);
    verify(io_exhausted(decoder.input) == true);

    verify(streq(example.name, "Triangle!!"));
    verify((void*) example.name == (void*) allocator.data);

    struct point* vertex = example.vertex;
    verify((void*) example.vertex == (void*) (allocator.data + 11));
    verify(vertex->x == 4);
    verify(vertex->y == 5);

    verify(allocator.allocations == 2);

  success();
    memory_release(&allocator);
}
