test( io_peek_socket, recv_success ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  when("the recv call succeeds");
    byte request[4] = { 'a', 'b', 'c', 'd' };
    recv_simulated_data = &io_reader(request, sizeof(request));


  calling("io_peek()");
    byte value[4];
    void* result = io_peek(&reader, value, sizeof(value));


  must("successfully read the io");
    verify(result != NULL);
    verify(value[0] == 'a');
    verify(value[1] == 'b');
    verify(value[2] == 'c');
    verify(value[3] == 'd');
    verify(reader.cursor == 0);
    verify(reader.length == 0);


  success();
}
