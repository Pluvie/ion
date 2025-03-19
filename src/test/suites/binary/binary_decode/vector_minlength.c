test( binary_decode, vector_minlength ) {

  given("an example struct with a vector type");
    struct example {
      struct vector bytes;
    } example;


  when("it has an associated reflection that enforces a minimum length");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(bytes, VECTOR, struct example),
            limited_to(4, 0), of({ type(BYTE) })
        },
      })
    };


  when("some input data is ready to decode, and the max length is not satisfied");
    byte input[] = {
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       /* bytes length */
      0x10,                                                 /* bytes.0 */
      0x11,                                                 /* bytes.1 */
      0x12,                                                 /* bytes.2 */
    };


  calling("binary_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, sizeof(input));
    binary_decode(&example, &source, &rfx, &allocator);


  must("fail to decode the input data and report the error properly");
    verify(error.occurred == true);
    verify(streq(error.message,
      "[bytes] vector required minimum length of 4 but found 3"));


  success();
    memory_release(&allocator);
}
