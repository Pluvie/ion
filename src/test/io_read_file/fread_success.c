test( io_read_file, fread_success ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_FILE,
      .allocator = &(struct buffer) { 0 },
      .length = 4,
    };


  when("the fread call succeeds");
    byte file[4] = { 'a', 'b', 'c', 'd' };
    fread_simulated_data = &io_memory(file, sizeof(file));


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
}
