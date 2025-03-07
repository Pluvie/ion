test( binary_encode, pointer ) {

  given("an example struct with a pointer type");
    struct example {
      char* name;
      struct point {
        i32 x;
        i32 y;
      } *vertex;
      struct array* coordinates;
    };


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
      })
    };


  when("some input data is ready to encode");
    struct example input = {
      .name = "Triangle!!",
      .vertex = &(struct point) {
        .x = 4,
        .y = 5,
      },
      .coordinates = &array_of(i32, { 7, 8 })
    };


  calling("binary_encode()");
    byte output[1024] = { 0 };
    struct io target = io_open_memory(output, sizeof(output));
    reflection_initialize(&rfx, &input, NULL);
    binary_encode(&rfx, &target);


  must("encode the input data on the struct correctly");
    byte expected_output[] = {
      0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* name size */
      0x54, 0x72, 0x69, 0x61, 0x6e, 0x67, 0x6c, 0x65,       /* name */
      0x21, 0x21, 0x00,

      0x04, 0x00, 0x00, 0x00,                               /* vertex->x */
      0x05, 0x00, 0x00, 0x00,                               /* vertex->y */

      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* coordinates length */
      0x07, 0x00, 0x00, 0x00,                               /* coordinates.1 */
      0x08, 0x00, 0x00, 0x00,                               /* coordinates.2 */
    };

    verify(error.occurred == false);
    verify(memeq(output, expected_output, sizeof(expected_output)) == true);


  success();
}
