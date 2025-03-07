test( io_read_file, buffered_retention_overflow ) {

  given("a file");
    char file[8192] = { 0 };
    memset(file, 'f', lengthof(file));
    fread_simulated_data = &io_open_memory(file, lengthof(file));


  when("a struct io is opened on that file");
    struct io reader = io_open_file(file);


  calling("io_read()");
    u32 cursor = 0;
    u32 reads_count = 0;
    char result[reader.length];

    for (; cursor < 1024; cursor++) {
      result[cursor] = *(char*) io_read(&reader, 1);
      reads_count++;
    }

    char* data = io_read(&reader, 5000);
    verify(reader.read_amount == 5000);
    memcpy(result + cursor, data, 5000);
    cursor += 5000;
    reads_count++;

    for(; cursor < reader.length; cursor++) {
      result[cursor] = *(char*) io_read(&reader, 1);
      reads_count++;
    }


  must("do a buffered read of the io");
    verify(fread_simulated_data->reads_count == 5);
    verify(reader.reads_count > 1024 + 1);
    verify(reader.reads_count == reads_count);
    verify(reader.buffer.allocator.capacity == 16384);
    verify(reader.buffer.allocator.position == 2048);
    verify(reader.buffer.begin == 7048);
    verify(strneq(result, file, reader.length));


  success();
    io_close(&reader);
}
