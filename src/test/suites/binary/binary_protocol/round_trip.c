test( binary_protocol, round_trip ) {

  given("an example struct with primitive types");
    struct example {
      u8 value_u8;      u16 value_u16;    u32 value_u32;    u64 value_u64;
      i8 value_i8;      i16 value_i16;    i32 value_i32;    i64 value_i64;
      d32 value_d32;    d64 value_d64;    d128 value_d128;
      byte value_byte;  char value_char;  bool value_bool;
    };
    struct example source = { 0 };
    struct example target = { 0 };


  when("it has an associated reflection");
    #define t struct example
    struct reflection rfx = {
      type(STRUCT, t), fields({
        { field(value_u8, U8, t) },
        { field(value_u16, U16, t) },
        { field(value_u32, U32, t) },
        { field(value_u64, U64, t) },
        { field(value_i8, I8, t) },
        { field(value_i16, I16, t) },
        { field(value_i32, I32, t) },
        { field(value_i64, I64, t) },
        { field(value_d32, D32, t) },
        { field(value_d64, D64, t) },
        { field(value_d128, D128, t) },
        { field(value_byte, BYTE, t) },
        { field(value_char, CHAR, t) },
        { field(value_bool, BOOL, t) },
      })
    };
    #undef t


  when("some input data is ready to encode");
    source.value_u8 = 1;
    source.value_u16 = 2;
    source.value_u32 = 3;
    source.value_u64 = 4;
    source.value_i8 = -1;
    source.value_i16 = -2;
    source.value_i32 = -3;
    source.value_i64 = -4;
    source.value_d32 = (3.0f / 256.0);
    source.value_d64 = (3.0 / 256.0);
    source.value_d128 = (3.0 / 256.0);
    source.value_byte = 0xff;
    source.value_char = 'F';
    source.value_bool = true;


  calling("binary_encode() and binary_decode()");
    byte wire[1024] = { 0 };

    struct io output = io_open_memory(wire, sizeof(wire));
    binary_encode(&source, &output, &rfx);

    struct memory allocator = memory_init(0);
    struct io input = io_open_memory(wire, sizeof(wire));
    binary_decode(&target, &input, &rfx, &allocator);


  must("encode the source data correctly and decode it on the target");
    verify(error.occurred == false);
    verify(target.value_u8 == 1);
    verify(target.value_u16 == 2);
    verify(target.value_u32 == 3);
    verify(target.value_u64 == 4);
    verify(target.value_i8 == -1);
    verify(target.value_i16 == -2);
    verify(target.value_i32 == -3);
    verify(target.value_i64 == -4);
    verify(target.value_d32 == 3.0f / 256.0f);
    verify(target.value_d64 == 3.0 / 256.0);
    verify(target.value_d128 == 3.0 / 256.0);
    verify(target.value_byte == 0xff);
    verify(target.value_char == 'F');
    verify(target.value_bool == true);


  success();
    memory_release(&allocator);
}
