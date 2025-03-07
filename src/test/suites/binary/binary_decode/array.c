test( binary_decode, array ) {

  given("an example struct with an array type");
    struct example {
      struct array one_dim;
      struct array two_dim;
      struct array three_dim;
    } example;

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


  when("some input data is ready to decode");
    byte input[] = {
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


  calling("binary_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, sizeof(input));
    reflection_initialize(&rfx, &example, &allocator);
    binary_decode(&source, &rfx);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(io_exhausted(&source) == true);

    struct element e;

    struct array* one_dim = &(example.one_dim);
    e = as(struct element, array_get(one_dim, 0));
    verify(e.a == 0);
    verify(e.b == 1);
    e = as(struct element, array_get(one_dim, 1));
    verify(e.a == 2);
    verify(e.b == 3);
    e = as(struct element, array_get(one_dim, 2));
    verify(e.a == 4);
    verify(e.b == 5);

    struct array* two_dim = &(example.two_dim);
    e = as(struct element, array_get((struct array*) array_get(two_dim, 0), 0));
    verify(e.a == 16);
    verify(e.b == 17);
    e = as(struct element, array_get((struct array*) array_get(two_dim, 0), 1));
    verify(e.a == 18);
    verify(e.b == 19);
    e = as(struct element, array_get((struct array*) array_get(two_dim, 1), 0));
    verify(e.a == 32);
    verify(e.b == 33);
    e = as(struct element, array_get((struct array*) array_get(two_dim, 1), 1));
    verify(e.a == 34);
    verify(e.b == 35);

    u8* v;
    struct array* three_dim = &(example.three_dim);
    v = array_get((struct array*)
          array_get((struct array*)
            array_get(three_dim, 0), 0), 0);
    verify(v[0] == 0);
    verify(v[1] == 1);
    v = array_get((struct array*)
          array_get((struct array*)
            array_get(three_dim, 0), 1), 0);
    verify(v[0] == 16);
    verify(v[1] == 17);
    v = array_get((struct array*)
          array_get((struct array*)
            array_get(three_dim, 1), 0), 0);
    verify(v[0] == 32);
    verify(v[1] == 33);
    v = array_get((struct array*)
          array_get((struct array*)
            array_get(three_dim, 1), 1), 0);
    verify(v[0] == 48);
    verify(v[1] == 49);
    v = array_get((struct array*)
          array_get((struct array*)
            array_get(three_dim, 2), 0), 0);
    verify(v[0] == 64);
    verify(v[1] == 65);
    v = array_get((struct array*)
          array_get((struct array*)
            array_get(three_dim, 2), 1), 0);
    verify(v[0] == 80);
    verify(v[1] == 81);


  success();
    memory_release(&allocator);
}
