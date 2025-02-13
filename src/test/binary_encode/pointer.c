focus_test( binary_encode, pointer ) {

  given("an example struct with a pointer type");
    struct example {
      char* name;
      struct point {
        i32 x;
        i32 y;
      } *vertex;
      struct array* coordinates;
    };


  when("it has an associated reflection")
    struct reflect reflection = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, name), type(POINTER, 32), of({ type(CHAR) }) },

        { field(struct example, vertex), type(POINTER), of({
            type(STRUCT, sizeof(struct point)), fields({
              { field(struct point, x), type(I32) },
              { field(struct point, y), type(I32) },
            })
          })
        },

        { field(struct example, coordinates), type(POINTER), of({
            type(ARRAY, 2, 2), of({
              type(I32)
            })
          })
        },
      })
    };


  when("some input data is ready to encode");
    struct example input = {
      .name = "Triangle!",
      .vertex = &(struct point) {
        .x = 4,
        .y = 5,
      },
      .coordinates = &array_of(i32, { 7, 8 })
    };


  calling("binary_encode()");
    byte output[1024] = { 0 };
    struct object source = object(input, &reflection);
    struct io target = io_writer(output, sizeof(output));
    binary_encode(&source, &target);


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

    print("");
    error_print();
    verify(error.occurred == false);
    print("");
    hexdump(output, sizeof(expected_output));
    verify(memeq(output, expected_output, sizeof(expected_output)) == true);


  success();
}
