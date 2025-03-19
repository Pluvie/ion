test( binary_decode, pointer ) {

  given("an example struct with a pointer type");
    struct example {
      char* name;
      struct point {
        i32 x;
        i32 y;
      } *vertex;
      struct array* coordinates;
      void* always_null;
    } example;


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(name, POINTER, struct example), limited_to(0, 32),
            of({ type(CHAR) })
        },

        { field(vertex, POINTER, struct example), of({
            type(STRUCT, struct point), fields({
              { field(x, I32, struct point) },
              { field(y, I32, struct point) },
            })
          })
        },

        { field(coordinates, POINTER, struct example), of({
            type(ARRAY), limited_to(2, 2), of({
              type(I32)
            })
          })
        },

        { field(always_null, POINTER, struct example),
            of({ type(BYTE) })
        },
      })
    };


  when("some input data is ready to decode");
    byte input[] = {
      0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* name size */
      0x54, 0x72, 0x69, 0x61, 0x6e, 0x67, 0x6c, 0x65,       /* name */
      0x21, 0x21, 0x00,

      0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* vertex ptr size */
      0x04, 0x00, 0x00, 0x00,                               /* vertex->x */
      0x05, 0x00, 0x00, 0x00,                               /* vertex->y */

      0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* coordinates ptr size */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* coordinates length */
      0x07, 0x00, 0x00, 0x00,                               /* coordinates.1 */
      0x08, 0x00, 0x00, 0x00,                               /* coordinates.2 */

      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* always_null ptr size */
    };


  calling("binary_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, sizeof(input));
    binary_decode(&example, &source, &rfx, &allocator);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(io_exhausted(&source) == true);

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

    verify(example.always_null == NULL);

    /* The total allocations must be: 3 (pointers) and 1 (array data). */
    verify(allocator.allocations == 3 + 1);


  success();
    memory_release(&allocator);
}
