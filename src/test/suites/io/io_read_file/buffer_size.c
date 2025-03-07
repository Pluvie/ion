test( io_read_file, buffer_size ) {

  given("a file");
    char file[8192] = { 0 };
    memset(file, 'f', lengthof(file));
    fread_simulated_data = &io_open_memory(file, lengthof(file));


  when("a struct io is opened on that file");
    struct io reader = io_open_file(file);


  when("the buffer of the io is set to a higher amount");
    reader.buffer.size = 8000;


  calling("io_read()");
    char result[reader.length];
    u32 reads_count = 0;
    for(u32 cursor = 0; cursor < reader.length; cursor++) {
      result[cursor] = *(char*) io_read(&reader, 1);
      reads_count++;
    }


  must("reduce the number of system calls");
    verify(fread_simulated_data->reads_count == 2);
    verify(reader.reads_count == reads_count);
    verify(reader.buffer.allocator.capacity == 16384);
    verify(reader.buffer.allocator.position == 16000);
    verify(reader.buffer.begin == 0);
    verify(strneq(result, file, reader.length));


  success();
    io_close(&reader);
}
