test( json_decode_number, parse_error ) {

  given("a json protocol and a schema with a number type");
    struct protocol json = { 0 };

    u64 example;

    struct reflect schema = {
      type(U64), .name = "example"
    };

    struct memory allocator = memory_init(4096);
    json.allocator = &allocator;
    json.schema = &schema;


  when("some input data is invalid to parse");
    char* input_data = " ABCD   ";


  calling("json_decode_number()");
    struct io input = io_reader(input_data, strlen(input_data));
    struct io output = io_writer(&example, sizeof(example));
    json_decode_number(&input, &output, &json);


  must("fail to decode with a specific error");
    verify(json.error.occurred == true);
    verify(streq(json.error.message,
      "[example] invalid JSON, unable to parse number: expected a number"));


  success();
    memory_release(&allocator);
}
