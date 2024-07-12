test( json_decode_number, success ) {

  given("a json protocol and a schema with a number type");
    struct protocol json = { 0 };

    u64 example;

    struct reflect schema = {
      type(U64), .name = "example"
    };

    struct memory allocator = memory_init(4096);
    json.allocator = &allocator;
    json.schema = &schema;


  when("some input data is ready to decode");
    char* input_data = " 1234567890   ";


  calling("json_decode_number()");
    struct io input = io_reader(input_data, strlen(input_data));
    struct io output = io_writer(&example, sizeof(example));
    json_decode_number(&input, &output, &json);


  must("decode the input data on the number correctly");
    verify(json.error.occurred == false);
    verify(io_exhausted(&input) == true);
    verify(example == 1234567890);


  success();
    memory_release(&allocator);
}
