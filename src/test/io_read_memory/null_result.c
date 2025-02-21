test( io_read_memory, null_result ) {

  given("a struct io");
    struct io reader = {
      .channel = IO_CHANNEL_MEM,
      .mode = IO_MODE_READ,
      .memory = (byte[]) { 0x00, 0x01, 0x02 },
      .length = 3,
    };


  when("the cursor is in a valid position");
    reader.cursor = 2;


  calling("io_read() with a NULL result pointer");
    void* result = io_read(&reader, NULL, 1);


  must("successfully read the io");
    verify(result != NULL);
    verify(*(byte*) result == 0x02);
    verify(reader.cursor == 3);


  success();
}
