test( binary_decode, sequence ) {

  given("a binary protocol and a reflection with a sequence type");
    struct example {
      char name[32];
      struct point {
        i32 x;
        i32 y;
      } vertexes[3];
    } example;


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


  when("some input data is ready to decode");
    byte input[] = {
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


  calling("binary_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_reader(input, sizeof(input));
    struct object target = object(example, &reflection, &allocator);
    binary_decode(&source, &target);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(io_exhausted(&source) == true);

    verify(streq(example.name, "Triangle!!"));

    struct point p;
    p = example.vertexes[0];
    verify(p.x == 1);
    verify(p.y == 1);
    p = example.vertexes[1];
    verify(p.x == 3);
    verify(p.y == 3);
    p = example.vertexes[2];
    verify(p.x == 7);
    verify(p.y == 9);


  success();
    memory_release(&allocator);
}
