test( binary_encode, array ) {

  given("an example struct with an array type");
    struct example {
      struct array one_dim;
      struct array two_dim;
      struct array three_dim;
    };

    struct element {
      i32 a;
      i32 b;
    };


  when("it has an associated reflection");
    struct reflection element_rfx = {
      type(STRUCT, struct element), fields({
        { field(a, I32, struct element) },
        { field(b, I32, struct element) },
      })
    };

    struct reflection rfx = {
      type(STRUCT, struct example), fields({

        { field(one_dim, ARRAY, struct example), of({
            type(STRUCT), reflect(&element_rfx)
          })
        },

        { field(two_dim, ARRAY, struct example), of({
            type(ARRAY), of({
              type(STRUCT), reflect(&element_rfx)
            })
          })
        },

        { field(three_dim, ARRAY, struct example), of({
            type(ARRAY), of({
              type(ARRAY), of({
                type(U8)
              })
            })
          })
        },
      })
    };


  when("some input data is ready to encode");
    struct example input = { 0 };
    input.one_dim = array_of(struct element, {
      { .a = 0, .b = 1 },
      { .a = 2, .b = 3 },
      { .a = 4, .b = 5 },
    });
    input.two_dim = array_of(struct array, {
      array_of(struct element, {
        { .a = 16, .b = 17 },
        { .a = 18, .b = 19 },
      }),
      array_of(struct element, {
        { .a = 32, .b = 33 },
        { .a = 34, .b = 35 },
        { .a = 36, .b = 37 },
      }),
    });
    input.three_dim = array_of(struct array, {
      array_of(struct array, {
        array_of(byte, { 0, 1 }),
        array_of(byte, { 16, 17 }),
      }),
      array_of(struct array, {
        array_of(byte, { 32, 33 }),
        array_of(byte, { 48, 49 }),
      }),
      array_of(struct array, {
        array_of(byte, { 64, 65 }),
        array_of(byte, { 80, 81 }),
      }),
    });


  calling("binary_encode()");
    byte wire[1024] = { 0 };
    struct io output = io_open_memory(wire, sizeof(wire));
    binary_encode(&input, &output, &rfx);


  must("encode the input data correctly");
    byte expected_wire[] = {
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* one_dim length */
      0x00, 0x00, 0x00, 0x00,                               /* one_dim.0.a */
      0x01, 0x00, 0x00, 0x00,                               /* one_dim.0.b */
      0x02, 0x00, 0x00, 0x00,                               /* one_dim.1.a */
      0x03, 0x00, 0x00, 0x00,                               /* one_dim.1.b */
      0x04, 0x00, 0x00, 0x00,                               /* one_dim.2.a */
      0x05, 0x00, 0x00, 0x00,                               /* one_dim.2.b */

      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* two_dim length */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* two_dim.0 length */
      0x10, 0x00, 0x00, 0x00,                               /* two_dim.0.0.a */
      0x11, 0x00, 0x00, 0x00,                               /* two_dim.0.0.b */
      0x12, 0x00, 0x00, 0x00,                               /* two_dim.0.1.a */
      0x13, 0x00, 0x00, 0x00,                               /* two_dim.0.1.b */
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* two_dim.1 length */
      0x20, 0x00, 0x00, 0x00,                               /* two_dim.1.0.a */
      0x21, 0x00, 0x00, 0x00,                               /* two_dim.1.0.b */
      0x22, 0x00, 0x00, 0x00,                               /* two_dim.1.1.a */
      0x23, 0x00, 0x00, 0x00,                               /* two_dim.1.1.b */
      0x24, 0x00, 0x00, 0x00,                               /* two_dim.1.2.a */
      0x25, 0x00, 0x00, 0x00,                               /* two_dim.1.2.b */

      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim length */

      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.0 length */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.0.0 length */
      0x00,                                                 /* three_dim.0.0.0 */
      0x01,                                                 /* three_dim.0.0.1 */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.0.1 length */
      0x10,                                                 /* three_dim.0.1.0 */
      0x11,                                                 /* three_dim.0.1.1 */

      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.1 length */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.1.0 length */
      0x20,                                                 /* three_dim.1.0.0 */
      0x21,                                                 /* three_dim.1.0.1 */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.1.1 length */
      0x30,                                                 /* three_dim.1.1.0 */
      0x31,                                                 /* three_dim.1.1.1 */

      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.2 length */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.2.0 length */
      0x40,                                                 /* three_dim.2.0.0 */
      0x41,                                                 /* three_dim.2.0.1 */
      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* three_dim.2.1 length */
      0x50,                                                 /* three_dim.2.1.0 */
      0x51,                                                 /* three_dim.2.1.1 */
    };

    verify(error.occurred == false);
    verify(memeq(wire, expected_wire, sizeof(expected_wire)) == true);


  success();
}
