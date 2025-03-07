test( io_read_socket, recv_success ) {

  given("a socket io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCKET,
    };


  when("the recv call succeeds");
    byte request[4] = { 'a', 'b', 'c', 'd' };
    recv_simulated_data = &io_open_memory(request, sizeof(request));


  calling("io_read()");
    byte* result = io_read(&reader, 4);


  must("successfully read the io");
    verify(result != NULL);
    verify(result[0] == 'a');
    verify(result[1] == 'b');
    verify(result[2] == 'c');
    verify(result[3] == 'd');
    verify(reader.cursor == 4);
    verify(reader.length == 4);


  success();
    io_close(&reader);
}
