test( io_read_socket, recv_failure ) {

  given("a socket io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCKET,
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
    io_close(&reader);
}
