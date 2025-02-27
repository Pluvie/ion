test( io_read_memory, valid_cursor ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_MEMORY,
      .memory = (byte[]) { 0x00, 0x01, 0x02 },
      .length = 3,
    };


  when("the cursor is in a valid position");
    reader.cursor = 2;


  calling("io_read()");
    byte* result = io_read(&reader, 1);


  must("successfully read the io");
    verify(result != NULL);
    verify(result[0] == 0x02);
    verify(reader.cursor == 3);


  success();
}
