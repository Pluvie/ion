test( io_read_file, fread_failure ) {

  given("a struct io");
    struct buffer allocator = buffer_init(0);
    struct io reader = {
      .channel = IO_CHANNEL_FILE,
      .allocator = &allocator,
      .length = 4,
    };


  when("the fread call fails");
    fread_simulated_data = NULL;


  calling("io_read()");
    byte* result = io_read(&reader, 4);


  must("not read the io");
    verify(result == NULL);
    verify(reader.cursor == 0);
    verify(reader.length == 4);


  success();
    buffer_release(&allocator);
}
