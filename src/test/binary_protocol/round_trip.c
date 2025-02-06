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


  when("it has an associated reflection")
    struct reflect reflection = {
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
        { field(struct example, value_byte), type(BYTE) },
        { field(struct example, value_char), type(CHAR) },
        { field(struct example, value_bool), type(BOOL) },
      })
    };


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
    struct memory allocator = memory_init(0);

    struct object encoder = object(source, &reflection);
    struct io binary_writer = io_writer(wire, sizeof(wire));
    struct io binary_reader = io_reader(wire, sizeof(wire));
    struct object decoder = object(target, &reflection, &allocator);
    binary_encode(&encoder, &binary_writer);
    binary_decode(&binary_reader, &decoder);


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
