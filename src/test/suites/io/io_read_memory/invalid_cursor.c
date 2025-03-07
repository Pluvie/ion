test( io_read_memory, invalid_cursor ) {

  given("a struct io");
    byte memory[] = { 0x00, 0x01, 0x02 };
    struct io reader = io_open_memory(memory, sizeof(memory));


  when("the cursor is in a invalid position");
    reader.cursor = 5;


  calling("io_read()");
    byte* result = io_read(&reader, 1);


  must("not read the io");
    verify(error.occurred == true);
    verify(streq(error.message, "io: end of memory reached"));
    verify(result == NULL);
    verify(reader.cursor == 5);


  success();
}
