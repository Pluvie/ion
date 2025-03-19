test( binary_encode, string ) {

  given("an example struct with a string type");
    struct example {
      struct string name;
      struct string empty;
    };


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(name, STRING, struct example) },
        { field(empty, STRING, struct example) },
      })
    };


  when("some input data is ready to encode");
    struct example input = {
      .name = s("Triangle!!"),
      .empty = (struct string) { 0 },
    };


  calling("binary_encode()");
    byte wire[1024] = { 0 };
    struct io output = io_open_memory(wire, sizeof(wire));
    binary_encode(&input, &output, &rfx);


  must("encode the input data on the struct correctly");
    byte expected_wire[] = {
      0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* name size */
      0x54, 0x72, 0x69, 0x61, 0x6e, 0x67, 0x6c, 0x65,       /* name */
      0x21, 0x21,

      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* empty size */
    };

    verify(error.occurred == false);
    verify(memeq(wire, expected_wire, sizeof(expected_wire)) == true);


  success();
}
