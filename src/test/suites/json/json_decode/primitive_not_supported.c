test( json_decode, primitive_not_supported ) {

  given("an example struct with primitive types not supported in JSON");
    struct example {
      bool value_bool; byte value_byte;  char value_char;
    } example;


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, value_bool), type(BOOL) },
        { field(struct example, value_byte), type(BYTE) },
        { field(struct example, value_char), type(CHAR) },
      })
    };


  when("some input data is ready to decode");
    char* input =
      " {"
      "   \"value_bool\": false,"
      "   \"value_byte\": \"0xff\","
      "   \"value_char\": \"A\","
      " }";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    struct object target = object(example, &rfx, &allocator);
    json_decode(&source, &target);


  must("fail to decode the input data with a specific error");
    char* expected_error =
      "[value_byte] primitive type `BYTE` not supported, at position 42:\n"
      "se,   \"value_byte\": \"0xff\",   \"value_cha\n"
      "                   ^";
    verify(error.occurred == true);
    verify(streq(expected_error, error.message));
    verify(example.value_bool == false);


  success();
    memory_release(&allocator);
}
