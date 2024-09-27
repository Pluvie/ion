test( binary_decode, primitive ) {

  given("an example struct with primitive types");
    struct example {
      u8 value_u8;      u16 value_u16;    u32 value_u32;    u64 value_u64;
      i8 value_i8;      i16 value_i16;    i32 value_i32;    i64 value_i64;
      d32 value_d32;    d64 value_d64;    d128 value_d128;
      byte value_byte;  char value_char;  bool value_bool;
    } example;


  when("it has an associated schema")
    struct reflect schema = {
      type(STRUCT, { sizeof(struct example), 14 }) {
        { field(value_u8, struct example), type(U8) },
        { field(value_u16, struct example), type(U16) },
        { field(value_u32, struct example), type(U32) },
        { field(value_u64, struct example), type(U64) },
        { field(value_i8, struct example), type(I8) },
        { field(value_i16, struct example), type(I16) },
        { field(value_i32, struct example), type(I32) },
        { field(value_i64, struct example), type(I64) },
        { field(value_d32, struct example), type(D32) },
        { field(value_d64, struct example), type(D64) },
        { field(value_d128, struct example), type(D128) },
        { field(value_byte, struct example), type(BYTE) },
        { field(value_char, struct example), type(CHAR) },
        { field(value_bool, struct example), type(BOOL) },
      }
    };


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


  when("a protocol decoder is set up on this data");
    struct memory allocator = memory_init(4096);
    struct protocol decoder = {
      .schema = &schema,
      .allocator = &allocator,
      .input = &io_reader(input, sizeof(input)),
      .output = &io_writer(&example, sizeof(example)),
    };


  calling("binary_decode()");
    binary_decode(&decoder);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(io_exhausted(decoder.input) == true);
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
