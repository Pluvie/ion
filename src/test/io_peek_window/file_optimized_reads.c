test( io_peek_window, file_optimized_reads ) {

  given("a file");
    char file[] =
      "\"Very long string that surpasses 256 characters, which is the default peek "
      "window of the json_parse_string function. The peek window is introduced to "
      "optimize io from file or sockets, where each io_read function call executes "
      "a system call -- fread for files, recv for sockets. Since JSON string parsing "
      "is done char by char, it would not be efficient to execute a system call for "
      "every character! Expecially for long strings like this one. So, the peek window "
      "is introduced, which peeks from the io a growing amount of characters, and saves "
      "it in memory -- using the struct buffer. Then, the actual character parsing is "
      "done by reading from memory, which is much more efficient.\"";


  when("an io is setup on that file");
    fread_simulated_data = &io_reader(file, sizeof(file));
    struct io input = {
      .channel = IO_CHANNEL_FILE,
      .mode = IO_MODE_READ,
      .length = sizeof(file),
    };


  calling("io_peek_window() repediately");
  must("increase gradually the peek window to optimize the reads");
    struct buffer buffer = { 0 };
    u64 max_position = U64_MAX;

    char* peek_window_1 = io_peek_window(&input, &buffer, &max_position);
    verify(error.occurred == false);
    verify(buffer.capacity == 256);
    verify(strneq(peek_window_1, file, buffer.capacity));

    char* peek_window_2 = io_peek_window(&input, &buffer, &max_position);
    verify(error.occurred == false);
    verify(buffer.capacity == 512);
    verify(strneq(peek_window_2, file, buffer.capacity));

    char* peek_window_3 = io_peek_window(&input, &buffer, &max_position);
    verify(error.occurred == false);
    verify(buffer.capacity == 1024);
    verify(strlen(peek_window_3) == strlen(file));
    verify(streq(peek_window_3, file));

    verify(input.reads_count == 3);


  success();
    buffer_release(&buffer);
}
