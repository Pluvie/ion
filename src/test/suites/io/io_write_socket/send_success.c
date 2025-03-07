test( io_write_socket, send_success ) {

  given("a struct io");
    struct io write = {
      .channel = IO_CHANNEL_SOCKET,
    };


  when("the send call succeeds");
    byte response[4] = { 0 };
    send_simulated_data = &io_open_memory(response, sizeof(response));


  calling("io_write()");
    byte value[4] = { 'a', 'b', 'c', 'd' };
    u64 amount = io_write(&write, value, sizeof(value));


  must("successfully write the io");
    verify(amount == 4);
    verify(response[0] == 'a');
    verify(response[1] == 'b');
    verify(response[2] == 'c');
    verify(response[3] == 'd');
    verify(write.cursor == 4);
    verify(write.length == 4);


  success();
}
