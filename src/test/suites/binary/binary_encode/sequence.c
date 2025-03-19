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
    struct reflection rfx = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(name, SEQUENCE, struct example), of({ type(CHAR) }) },

        { field(vertexes, SEQUENCE, struct example), of({
            type(STRUCT, struct point), fields({
              { field(x, I32, struct point) },
              { field(y, I32, struct point) },
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
    byte wire[1024] = { 0 };
    struct io output = io_open_memory(wire, sizeof(wire));
    binary_encode(&input, &output, &rfx);


  must("encode the input data on the struct correctly");
    byte expected_wire[] = {
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
    verify(memeq(wire, expected_wire, sizeof(expected_wire)) == true);


  success();
}
