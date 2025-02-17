test( io_peek_socket, recv_success ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  when("the reader has an allocator");
    struct buffer allocator = buffer_init(0);
    reader.allocator = &allocator;


  when("the recv call succeeds");
    byte request[4] = { 'a', 'b', 'c', 'd' };
    recv_simulated_data = &io_reader(request, sizeof(request));


  calling("io_peek()");
    byte* value = io_peek(&reader, 4);


  must("successfully read the io");
    verify(value != NULL);
    verify(value[0] == 'a');
    verify(value[1] == 'b');
    verify(value[2] == 'c');
    verify(value[3] == 'd');
    verify(reader.cursor == 0);
    verify(reader.length == 4);


  success();
    buffer_release(&allocator);
}
