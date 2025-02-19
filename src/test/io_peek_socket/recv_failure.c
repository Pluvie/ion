test( io_peek_socket, recv_failure ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  when("the recv call fails");
    recv_simulated_data = NULL;


  calling("io_peek()");
    byte value[4];
    void* result = io_read(&reader, value, sizeof(value));


  must("not read the io");
    verify(result == NULL);
    verify(reader.cursor == 0);
    verify(reader.length == 0);


  success();
}
