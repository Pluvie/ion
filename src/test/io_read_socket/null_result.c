test( io_read_socket, null_result ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  when("the recv call succeeds");
    byte request[4] = { 'a', 'b', 'c', 'd' };
    recv_simulated_data = &io_reader(request, sizeof(request));


  calling("io_read() with a NULL result pointer");
    void* result = io_read(&reader, NULL, 4);


  must("successfully read the io and discard the result");
    verify(result == NULL);
    verify(reader.cursor == 4);
    verify(reader.length == 4);


  success();
}
