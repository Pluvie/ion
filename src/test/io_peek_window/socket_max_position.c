test( io_peek_window, socket_max_position ) {

  given("a socket");
    char sock[] = "\"example string\"";


  when("an io is setup on that socket");
    recv_simulated_data = &io_reader(sock, sizeof(sock));
    struct io input = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  calling("io_peek_window()");
    struct buffer buffer = { 0 };
    u64 max_position = U64_MAX;
    char* peek_window = io_peek_window(&input, &buffer, &max_position);


  must("peek the correct max position");
    verify(error.occurred == false);
    verify(max_position == sizeof(sock));
    verify(streq(peek_window, sock));
    verify(input.reads_count == 1);


  success();
    buffer_release(&buffer);
}
