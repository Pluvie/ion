test( io_write_memory, valid_cursor ) {

  given("a struct io");
    struct io writer = {
      .channel = IO_CHANNEL_MEMORY,
      .memory = (byte[]) { 0x00, 0x01, 0x00 },
      .length = 3,
    };


  when("the cursor is in a valid position");
    writer.cursor = 2;


  calling("io_write()");
    byte value = 0x02;
    u64 amount = io_write(&writer, &value, 1);


  must("successfully write the io");
    verify(amount == 1);
    verify(((byte*) writer.memory)[2] == 0x02);
    verify(writer.cursor == 3);


  success();
}
