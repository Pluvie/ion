test( binary_encode, sequence ) {

  given("a binary protocol and a reflection with a sequence type");
    struct example {
      char name[32];
      struct point {
        i32 x;
        i32 y;
      } vertexes[3];
    };


  when("it has an associated reflection");
    struct reflect reflection = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, name), type(SEQUENCE, 32), of({ type(CHAR) }) },

        { field(struct example, vertexes), type(SEQUENCE, 3), of({
            type(STRUCT, sizeof(struct point)), fields({
              { field(struct point, x), type(I32) },
              { field(struct point, y), type(I32) },
            })
          })
        },
      })
    };


  when("some input data is ready to encode");
    struct example input = {
      .name = "Triangle!!",
      .vertexes = {
        { .x = 1, .y = 1, },
        { .x = 3, .y = 3, },
        { .x = 7, .y = 9, },
      },
    };


  calling("binary_encode()");
    byte output[1024] = { 0 };
    struct object source = object(input, &reflection);
    struct io target = io_writer(output, sizeof(output));
    binary_encode(&source, &target);


  must("encode the input data on the struct correctly");
    byte expected_output[] = {
      0x54, 0x72, 0x69, 0x61, 0x6e, 0x67, 0x6c, 0x65,       /* name */
      0x21, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

      0x01, 0x00, 0x00, 0x00,                               /* vertexes.0.x */
      0x01, 0x00, 0x00, 0x00,                               /* vertexes.0.y */
      0x03, 0x00, 0x00, 0x00,                               /* vertexes.1.x */
      0x03, 0x00, 0x00, 0x00,                               /* vertexes.1.y */
      0x07, 0x00, 0x00, 0x00,                               /* vertexes.2.x */
      0x09, 0x00, 0x00, 0x00,                               /* vertexes.2.y */
    };

    verify(error.occurred == false);
    verify(memeq(output, expected_output, sizeof(expected_output)) == true);


  success();
}
