test( io_read_file, fread_success ) {

  given("a file io");
    void* file = "abcd";
    struct io reader = io_open_file(file);
    reader.length = strlen(file);


  when("the fread call succeeds");
    fread_simulated_data = &io_open_memory(file, sizeof(file));


  calling("io_read()");
    byte* result = io_read(&reader, 4);


  must("successfully read the io");
    verify(result != NULL);
    verify(result[0] == 'a');
    verify(result[1] == 'b');
    verify(result[2] == 'c');
    verify(result[3] == 'd');
    verify(reader.cursor == 4);
    verify(reader.length == 4);


  success();
    io_close(&reader);
}
