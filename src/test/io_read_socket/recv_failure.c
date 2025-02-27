test( io_read_socket, recv_failure ) {

  given("a struct io");
    struct buffer allocator = buffer_init(0);
    struct io reader = {
      .channel = IO_CHANNEL_SOCKET,
      .allocator = &allocator,
    };


  when("the recv call fails");
    recv_simulated_data = NULL;


  calling("io_read()");
    byte* result = io_read(&reader, 4);


  must("not read the io");
    verify(result == NULL);
    verify(reader.cursor == 0);
    verify(reader.length == 0);


  success();
    buffer_release(&allocator);
}
