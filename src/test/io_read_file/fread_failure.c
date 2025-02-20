test( io_read_file, fread_failure ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_FILE,
      .mode = IO_MODE_READ,
      .length = 4,
    };


  when("the fread call fails");
    fread_simulated_data = NULL;


  calling("io_read()");
    byte value[4];
    void* result = io_read(&reader, value, sizeof(value));


  must("not read the io");
    verify(result == NULL);
    verify(reader.cursor == 0);
    verify(reader.length == 4);


  success();
}
