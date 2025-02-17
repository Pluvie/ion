test( io_peek_socket, recv_failure ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  when("the reader has an allocator");
    struct buffer allocator = buffer_init(0);
    reader.allocator = &allocator;


  when("the recv call fails");
    recv_simulated_data = NULL;


  calling("io_peek()");
    byte* value = io_peek(&reader, 4);


  must("successfully read the io");
    verify(value == NULL);
    verify(reader.cursor == 0);
    verify(reader.length == 0);


  success();
    buffer_release(&allocator);
}
