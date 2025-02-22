test( io_peek_window, socket_optimized_reads ) {

  given("a socket");
    char sock[] =
      "\"Very long string that surpasses 256 characters, which is the default peek "
      "window of the json_parse_string function. The peek window is introduced to "
      "optimize io from file or sockets, where each io_read function call executes "
      "a system call -- fread for files, recv for sockets. Since JSON string parsing "
      "is done char by char, it would not be efficient to execute a system call for "
      "every character! Expecially for long strings like this one. So, the peek window "
      "is introduced, which peeks from the io a growing amount of characters, and saves "
      "it in memory -- using the struct buffer. Then, the actual character parsing is "
      "done by reading from memory, which is much more efficient.\"";


  when("an io is setup on that socket");
    recv_simulated_data = &io_reader(sock, sizeof(sock));
    struct io input = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  calling("io_peek_window() repediately");
  must("increase gradually the peek window to optimize the reads");
    struct buffer buffer = { 0 };
    u64 max_position = U64_MAX;

    char* peek_window_1 = io_peek_window(&input, &buffer, &max_position);
    verify(error.occurred == false);
    verify(buffer.capacity == 256);
    verify(strneq(peek_window_1, sock, buffer.capacity));

    char* peek_window_2 = io_peek_window(&input, &buffer, &max_position);
    verify(error.occurred == false);
    verify(buffer.capacity == 512);
    verify(strneq(peek_window_2, sock, buffer.capacity));

    char* peek_window_3 = io_peek_window(&input, &buffer, &max_position);
    verify(error.occurred == false);
    verify(buffer.capacity == 1024);
    verify(strlen(peek_window_3) == strlen(sock));
    verify(streq(peek_window_3, sock));

    verify(input.reads_count == 3);


  success();
    buffer_release(&buffer);
}
