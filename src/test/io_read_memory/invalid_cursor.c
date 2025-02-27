test( io_read_memory, invalid_cursor ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_MEMORY,
      .memory = (byte[]) { 0x00, 0x01, 0x02 },
      .length = 3,
    };


  when("the cursor is in a invalid position");
    reader.cursor = 5;


  calling("io_read()");
    byte* result = io_read(&reader, 1);


  must("not read the io");
    verify(error.occurred == true);
    verify(streq(error.message, "io: end of input reached"));
    verify(result == NULL);
    verify(reader.cursor == 5);


  success();
}
