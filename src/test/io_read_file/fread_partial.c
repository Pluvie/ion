test( io_read_file, fread_partial ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_FILE,
      .mode = IO_MODE_READ,
      .length = 4,
    };


  when("the fread call succeeds, but has partial data");
    byte request[4] = { 'a', 'b', 'c', 'd' };
    fread_simulated_data = &io_reader(request, sizeof(request));


  calling("io_read()");
    byte value[8];
    void* result = io_read(&reader, value, sizeof(value));


  must("successfully read the io, but with partial data only");
    verify(result != NULL);
    verify(value[0] == 'a');
    verify(value[1] == 'b');
    verify(value[2] == 'c');
    verify(value[3] == 'd');
    verify(reader.cursor == 4);
    verify(reader.length == 4);


  success();
}
