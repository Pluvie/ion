focus_test( json_decode, struct ) {
  print("");

  given("a example struct");
    struct example {
      u8 number;
      char* string;
    } example;


  when("it has an associated reflection")
    struct reflect reflection = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, number), type(U8) },
        { field(struct example, string), type(POINTER), of({ type(CHAR) }) },
      })
    };


  when("some input data is ready to decode");
    char* input =
      " {"
      "   \"number\": 255,"
      "   \"example_string\": \"example\","
      " }";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_reader(input, sizeof(input));
    struct object target = object(example, &reflection, &allocator);
    json_decode(&source, &target);


  must("decode the input data on the struct correctly");
    error_print();
    verify(error.occurred == false);
    verify(example.number == 255);


  success();
    memory_release(&allocator);
}
