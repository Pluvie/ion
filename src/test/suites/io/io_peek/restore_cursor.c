test( io_peek, restore_cursor ) {

  given("a struct io");
    byte memory[] = { 0x00, 0x01, 0x02 };
    struct io reader = io_open_memory(memory, sizeof(memory));


  when("the cursor is in a valid position");
    reader.cursor = 2;


  calling("io_peek()");
    byte* result = io_peek(&reader, 1);


  must("successfully read the io and restore the cursor position");
    verify(result != NULL);
    verify(result[0] == 0x02);
    verify(reader.cursor == 2);


  success();
}
