test( io_write_file, fwrite_success ) {

  given("a struct io");
    struct io writer = {
      .channel = IO_CHANNEL_FILE,
    };


  when("the fwrite call succeeds");
    byte file[4] = { 0 };
    fwrite_simulated_data = &io_open_memory(file, sizeof(file));


  calling("io_write()");
    byte value[4] = { 0x00, 0x01, 0x02, 0x03 };
    u64 amount = io_write(&writer, value, sizeof(value));


  must("not write the io");
    verify(amount == 4);
    verify(writer.cursor == 4);
    verify(writer.length == 4);
    verify(file[0] == 0x00);
    verify(file[1] == 0x01);
    verify(file[2] == 0x02);
    verify(file[3] == 0x03);


  success();
}
