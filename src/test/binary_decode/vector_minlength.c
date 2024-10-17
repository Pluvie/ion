test( binary_decode, vector_minlength ) {

  given("an example struct with a vector type");
    struct example {
      struct vector bytes;
    } example;


  when("it has an associated schema that enforces a minimum length")
    struct reflect schema = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, bytes), type(VECTOR, 4, 0), of({ type(BYTE) }) },
      })
    };


  when("some input data is ready to decode, and the max length is not satisfied");
    byte input[] = {
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* bytes length */
      0x10,                                                 /* bytes.0 */
      0x11,                                                 /* bytes.1 */
      0x12,                                                 /* bytes.2 */
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


  must("fail to decode the input data and report the error properly");
    verify(error.occurred == true);
    verify(streq(error.message,
      "[bytes] vector required minimum length of 4 but found 3"));

  success();
    error_reset();
    memory_release(&allocator);
}
