test( io_read_memory, valid_cursor ) {

  given("a struct io");
    byte memory[] = { 0x00, 0x01, 0x02 };
    struct io reader = io_open_memory(memory, sizeof(memory));


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
