test( binary_decode, string ) {

  given("an example struct with a string type");
    struct example {
      struct string name;
      struct string empty;
    } example;


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(name, STRING, struct example) },
        { field(empty, STRING, struct example) },
      })
    };


  when("some input data is ready to decode");
    byte input[] = {
      0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* name size */
      0x54, 0x72, 0x69, 0x61, 0x6e, 0x67, 0x6c, 0x65,       /* name */
      0x21, 0x21,

      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* empty size */
    };


  calling("binary_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, sizeof(input));
    binary_decode(&example, &source, &rfx, &allocator);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(io_exhausted(&source) == true);

    verify(string_equal(&(example.name), &s("Triangle!!")));
    verify(example.empty.content == NULL);


  success();
    memory_release(&allocator);
}
