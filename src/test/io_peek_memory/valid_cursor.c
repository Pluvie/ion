test( io_peek_memory, valid_cursor ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_MEM,
      .mode = IO_MODE_READ,
      .memory = (byte[]) { 0x00, 0x01, 0x02 },
      .length = 3,
    };


  when("the cursor is in a valid position");
    reader.cursor = 2;


  calling("io_peek()");
    byte value;
    void* result = io_peek(&reader, &value, 1);


  must("successfully read the io");
    verify(result != NULL);
    verify(value == 0x02);
    verify(reader.cursor == 2);


  success();
}
