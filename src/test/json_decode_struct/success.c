test( json_decode_struct, success ) {

  given("a json protocol and a schema with a struct type");
    struct protocol json = { 0 };

    struct example {
      u8 value_u8;
    } example;

    struct reflect schema = {
      type(STRUCT, { sizeof(struct example), 1 }) {
        { field(struct example, value_u8), type(U8) },
      }
    };

    struct memory allocator = memory_init(4096);
    json.allocator = &allocator;
    json.schema = &schema;


  when("some input data is ready to decode");
    char* input_data = " { \"value_u8\": 123  \n\n  }";


  calling("json_decode_struct()");
    struct io input = io_reader(input_data, strlen(input_data));
    struct io output = io_writer(&example, sizeof(example));
    json_decode_struct(&input, &output, &json);


  must("decode the input data on the struct correctly");
    verify(json.error.occurred == false);
    verify(io_exhausted(&input) == true);
    verify(example.value_u8 == 123);


  success();
    memory_release(&allocator);
}
