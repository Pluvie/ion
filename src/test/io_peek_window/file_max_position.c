test( io_peek_window, file_max_position ) {

  given("a file");
    char file[] = "\"example string\"";


  when("an io is setup on that file");
    fread_simulated_data = &io_reader(file, sizeof(file));
    struct io input = {
      .channel = IO_CHANNEL_FILE,
      .mode = IO_MODE_READ,
      .length = sizeof(file),
    };


  calling("io_peek_window()");
    struct buffer buffer = { 0 };
    u64 max_position = U64_MAX;
    char* peek_window = io_peek_window(&input, &buffer, &max_position);


  must("peek the correct max position");
    verify(error.occurred == false);
    verify(max_position == sizeof(file));
    verify(streq(peek_window, file));
    verify(input.reads_count == 1);


  success();
    buffer_release(&buffer);
}
