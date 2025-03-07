test( io_write_file, fwrite_failure ) {

  given("a struct io");
    struct io writer = {
      .channel = IO_CHANNEL_FILE,
      .length = 4,
    };


  when("the fwrite call fails");
    fwrite_simulated_data = NULL;


  calling("io_write()");
    byte value[4] = { 0x00, 0x01, 0x02, 0x03 };
    u64 amount = io_write(&writer, value, sizeof(value));


  must("not write the io");
    verify(amount == 0);
    verify(writer.cursor == 0);
    verify(writer.length == 4);


  success();
}
