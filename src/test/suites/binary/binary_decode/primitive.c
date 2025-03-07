test( binary_decode, primitive ) {

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


  when("some input data is ready to decode");
    byte input[] = {
      0x01,                                                 /* 1 */
      0x02, 0x00,                                           /* 2 */
      0x03, 0x00, 0x00, 0x00,                               /* 3 */
      0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* 4 */

      0xff,                                                 /* -1 */
      0xfe, 0xff,                                           /* -2 */
      0xfd, 0xff, 0xff, 0xff,                               /* -3 */
      0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,       /* -4 */

      0x00, 0x00, 0x40, 0x3c,                               /* 3 / 256 */
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x3f,       /* 3 / 256 */

      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,       /* 3 / 256 */
      0xf8, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

      0xff,                                                 /* 0xff */

      0x46,                                                 /* F */

      0x07,                                                 /* true */
    };


  calling("binary_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, sizeof(input));
    reflection_initialize(&rfx, &example, &allocator);
    binary_decode(&source, &rfx);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(io_exhausted(&source) == true);
    verify(example.value_u8 == 1);
    verify(example.value_u16 == 2);
    verify(example.value_u32 == 3);
    verify(example.value_u64 == 4);
    verify(example.value_i8 == -1);
    verify(example.value_i16 == -2);
    verify(example.value_i32 == -3);
    verify(example.value_i64 == -4);
    verify(example.value_d32 == 3.0f / 256.0f);
    verify(example.value_d64 == 3.0 / 256.0);
    verify(example.value_d128 == 3.0 / 256.0);
    verify(example.value_byte == 0xff);
    verify(example.value_char == 'F');
    verify(example.value_bool == true);


  success();
    memory_release(&allocator);
}
