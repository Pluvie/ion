test( json_decode_number, convert_error ) {

  given("a json protocol and a schema with a number type");
    struct protocol json = { 0 };

    u16 example;

    struct reflect schema = {
      type(U16), .name = "example"
    };

    struct memory allocator = memory_init(4096);
    json.allocator = &allocator;
    json.schema = &schema;


  when("some input data is valid to parse but fails to convert");
    char* input_data = " 456789   ";


  calling("json_decode_number()");
    struct io input = io_reader(input_data, strlen(input_data));
    struct io output = io_writer(&example, sizeof(example));
    json_decode_number(&input, &output, &json);


  must("fail to decode with a specific error");
    verify(json.error.occurred == true);
    verify(streq(json.error.message,
      "[example] cannot convert 456789 to (U16): value overflow"));


  success();
    memory_release(&allocator);
}
