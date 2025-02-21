test( io_read_file, null_result ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_FILE,
      .mode = IO_MODE_READ,
      .length = 4,
    };


  when("the fread call succeeds");
    byte file[4] = { 'a', 'b', 'c', 'd' };
    fread_simulated_data = &io_reader(file, sizeof(file));


  calling("io_read() with a NULL result pointer");
    void* result = io_read(&reader, NULL, 4);


  must("successfully read the io and discard the result");
    verify(result == NULL);
    verify(reader.cursor == 4);
    verify(reader.length == 4);


  success();
}
