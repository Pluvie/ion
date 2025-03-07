test( io_read_file, buffer_size_overflow ) {

  given("a file");
    char file[8192] = { 0 };
    memset(file, 'f', lengthof(file));
    fread_simulated_data = &io_open_memory(file, strlen(file));


  when("a struct io is opened on that file");
    struct io reader = io_open_file(file);


  calling("io_read() with an amount greater than the buffer size");
    char* result = io_read(&reader, 16384);


  must("reduce the number of system calls");
    verify(fread_simulated_data->reads_count == 1);
    verify(reader.reads_count == 1);
    verify(reader.read_amount == lengthof(file));
    verify(reader.buffer.allocator.capacity == next_pow2(lengthof(file)));
    verify(reader.buffer.allocator.position == lengthof(file));
    verify(reader.buffer.begin == 0);
    verify(strneq(result, file, reader.length));


  success();
    io_close(&reader);
}
