test( json_decode, primitive ) {

  given("an example struct with primitive types");
    struct example {
      u8 value_u8;      u16 value_u16;    u32 value_u32;    u64 value_u64;
      i8 value_i8;      i16 value_i16;    i32 value_i32;    i64 value_i64;
      d32 value_d32;    d64 value_d64;    d128 value_d128;
      byte value_byte;  char value_char;  bool value_bool;
    } example;


  when("it has an associated reflection");
    #define t struct example
    struct reflection rfx = {
      type(STRUCT, t), fields({
        { field(value_u8,   U8,   t) },
        { field(value_u16,  U16,  t) },
        { field(value_u32,  U32,  t) },
        { field(value_u64,  U64,  t) },
        { field(value_i8,   I8,   t) },
        { field(value_i16,  I16,  t) },
        { field(value_i32,  I32,  t) },
        { field(value_i64,  I64,  t) },
        { field(value_d32,  D32,  t) },
        { field(value_d64,  D64,  t) },
        { field(value_d128, D128, t) },
        { field(value_bool, BOOL, t) },
      })
    };
    #undef t


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
    reflection_initialize(&rfx, &example, &allocator);
    json_decode(&source, &rfx);


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
