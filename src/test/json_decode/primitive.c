test( json_decode, primitive ) {

  given("a json protocol and a reflection with primitive types");
    struct protocol json;

    struct example {
      u8 value_u8;      u16 value_u16;    u32 value_u32;    u64 value_u64;
      i8 value_i8;      i16 value_i16;    i32 value_i32;    i64 value_i64;
      d32 value_d32;    d64 value_d64;    d128 value_d128;
      byte value_byte;  char value_char;  bool value_bool;
    } example;

    struct reflect reflection = {
      type(STRUCT, { sizeof(struct example), 14 }) {
        { field(struct example, value_u8), type(U8) },
        { field(struct example, value_u16), type(U16) },
        { field(struct example, value_u32), type(U32) },
        { field(struct example, value_u64), type(U64) },
        { field(struct example, value_i8), type(I8) },
        { field(struct example, value_i16), type(I16) },
        { field(struct example, value_i32), type(I32) },
        { field(struct example, value_i64), type(I64) },
        { field(struct example, value_d32), type(D32) },
        { field(struct example, value_d64), type(D64) },
        { field(struct example, value_d128), type(D128) },
        { field(struct example, value_byte), type(BYTE) },
        { field(struct example, value_char), type(CHAR) },
        { field(struct example, value_bool), type(BOOL) },
      }
    };

    struct memory allocator = memory_init(4096);
    json.allocator = &allocator;
    json.reflection = &schema;


  when("some input data is ready to decode");
    char* input_data =
      " {"
      "   \"value_char\": \"Q\","
      "   \"value_byte\": 255,"
      " }";


  calling("json_decode()");
    json.decode = json_decode;
    struct io input = io_reader(input_data, strlen(input_data));
    struct io output = io_writer(&example, sizeof(example));
    decode(&json, &input, &output);


  must("decode the input data on the struct correctly");
    verify(json.error.occurred == false);
    verify(io_exhausted(&input) == true);
    //verify(example.value_u8 == 1);
    //verify(example.value_u16 == 2);
    //verify(example.value_u32 == 3);
    //verify(example.value_u64 == 4);
    //verify(example.value_i8 == -1);
    //verify(example.value_i16 == -2);
    //verify(example.value_i32 == -3);
    //verify(example.value_i64 == -4);
    //verify(example.value_d32 == 3.0f / 256.0f);
    //verify(example.value_d64 == 3.0 / 256.0);
    //verify(example.value_d128 == 3.0 / 256.0);
    verify(example.value_byte == 0xff);
    verify(example.value_char == 'Q');
    //verify(example.value_bool == true);


  success();
    memory_release(&allocator);
}
