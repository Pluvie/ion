test( io_read_memory, valid_cursor ) {

  given("a struct io");
    struct io reader = {
      .type = IO_TYPE_MEM,
      .flags = IO_READ,
      .data = (byte[]) { 0x00, 0x01, 0x02 },
      .length = 3,
    };


  when("the cursor is in a valid position");
    reader.cursor = 2;


  calling("io_read()");
    byte* value = io_read(&reader, 1);


  must("successfully read the io");
    verify(value != NULL);
    verify(*value == 0x02);
    verify(reader.cursor == 3);


  success();
}
