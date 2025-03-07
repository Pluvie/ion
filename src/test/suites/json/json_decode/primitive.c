test( json_decode, primitive ) {

  given("an example struct with primitive types");
    struct example {
      u8 value_u8;      u16 value_u16;    u32 value_u32;    u64 value_u64;
      i8 value_i8;      i16 value_i16;    i32 value_i32;    i64 value_i64;
      d32 value_d32;    d64 value_d64;    d128 value_d128;
      byte value_byte;  char value_char;  bool value_bool;
    } example;


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, sizeof(struct example)), fields({
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
        { field(struct example, value_bool), type(BOOL) },
      })
    };


  when("some input data is ready to decode");
    char* input =
      " {"
      "   \"value_u8\": 1,"
      "   \"value_u16\": 20,"
      "   \"value_u32\": 300,"
      "   \"value_u64\": 4000,"
      "   \"value_i8\": -1,"
      "   \"value_i16\": -20,"
      "   \"value_i32\": -300,"
      "   \"value_i64\": -4000,"
      "   \"value_d32\": 0.1171875,"
      "   \"value_d64\": 1.171875e-1,"
      "   \"value_d128\": 117.1875E-3,"
      "   \"value_bool\": true"
      " }";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    struct object target = object(example, &rfx, &allocator);
    json_decode(&source, &target);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(example.value_u8 == 1);
    verify(example.value_u16 == 20);
    verify(example.value_u32 == 300);
    verify(example.value_u64 == 4000);
    verify(example.value_i8 == -1);
    verify(example.value_i16 == -20);
    verify(example.value_i32 == -300);
    verify(example.value_i64 == -4000);
    verify(example.value_d32 == 0.1171875f);
    verify(example.value_d64 == 0.1171875);
    verify(example.value_d128 == 0.1171875);
    verify(example.value_bool == true);


  success();
    memory_release(&allocator);
}
