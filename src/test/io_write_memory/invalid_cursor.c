test( io_write_memory, invalid_cursor ) {

  given("a struct io");
    struct io writer = {
      .channel = IO_CHANNEL_MEMORY,
      .memory = (byte[]) { 0x00, 0x01, 0x00 },
      .length = 3,
    };


  when("the cursor is in a invalid position");
    writer.cursor = 5;


  calling("io_write()");
    byte value = 0x02;
    u64 amount = io_write(&writer, &value, 1);


  must("not write the io");
    verify(error.occurred == true);
    verify(streq(error.message, "io: unable to write, memory exhausted"));
    verify(amount == 0);
    verify(writer.cursor == 5);


  success();
}
