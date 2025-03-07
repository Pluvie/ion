test( io_read_file, buffered_retention ) {

  given("a file");
    char file[4096] = { 0 };
    memset(file, 'f', lengthof(file));
    fread_simulated_data = &io_open_memory(file, lengthof(file));


  when("a struct io is opened on that file");
    struct io reader = io_open_file(file);


  calling("io_read()");
    char result[reader.length];
    for (u32 i = 0; i < reader.length; i++)
      result[i] = *(char*) io_read(&reader, 1);


  must("do a buffered read of the io");
    verify(fread_simulated_data->reads_count == 4);
    verify(reader.reads_count == reader.length);
    verify(reader.buffer.allocator.capacity == 4*reader.buffer.size);
    verify(reader.buffer.allocator.position == 2*reader.buffer.size);
    verify(reader.buffer.begin == 2*reader.buffer.size);
    verify(strneq(result, file, reader.length));


  success();
    io_close(&reader);
}
