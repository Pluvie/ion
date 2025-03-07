test( io_write_socket, send_failure ) {

  given("a struct io");
    struct io writer = {
      .channel = IO_CHANNEL_SOCKET,
    };


  when("the send call fails");
    send_simulated_data = NULL;


  calling("io_write()");
    byte value[4];
    u64 amount = io_write(&writer, value, sizeof(value));


  must("not write the io");
    verify(amount == 0);
    verify(writer.cursor == 0);
    verify(writer.length == 0);


  success();
}
