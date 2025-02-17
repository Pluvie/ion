test( io_peek_socket, recv_partial ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  when("the reader has an allocator");
    struct buffer allocator = buffer_init(0);
    reader.allocator = &allocator;


  when("the recv call succeeds, but has partial data");
    byte request[4] = { 'a', 'b', 'c', 'd' };
    recv_simulated_data = &io_reader(request, sizeof(request));


  calling("io_peek()");
    byte* value = io_peek(&reader, 8);


  must("successfully read the io, but with partial data only");
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
