test( io_read_memory, invalid_cursor ) {

  given("a struct io");
    struct io reader = {
      .type = IO_TYPE_MEM,
      .flags = IO_READ,
      .data = (byte[]) { 0x00, 0x01, 0x02 },
      .length = 3,
    };


  when("the cursor is in a invalid position");
    reader.cursor = 5;


  calling("io_read()");
    byte* value = io_read(&reader, 1);


  must("not read the io");
    verify(value == NULL);
    verify(reader.cursor == 5);


  success();
}
