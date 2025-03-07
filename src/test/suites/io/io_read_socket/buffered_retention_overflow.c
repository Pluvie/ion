test( io_read_socket, buffered_retention_overflow ) {

  given("a socket");
    char sock[8192] = { 0 };
    memset(sock, 'f', lengthof(sock));
    recv_simulated_data = &io_open_memory(sock, lengthof(sock));


  when("a struct io is opened on that socket");
    struct io reader = io_open_socket(0);


  calling("io_read()");
    u32 cursor = 0;
    u32 reads_count = 0;
    char result[lengthof(sock)];

    for (; cursor < 1024; cursor++) {
      result[cursor] = *(char*) io_read(&reader, 1);
      reads_count++;
    }

    char* data = io_read(&reader, 5000);
    verify(reader.read_amount == 5000);
    memcpy(result + cursor, data, 5000);
    cursor += 5000;
    reads_count++;

    for(; cursor < lengthof(sock); cursor++) {
      result[cursor] = *(char*) io_read(&reader, 1);
      reads_count++;
    }


  must("do a buffered read of the io");
    verify(recv_simulated_data->reads_count == 5);
    verify(reader.reads_count > 1024 + 1);
    verify(reader.reads_count == reads_count);
    verify(reader.buffer.allocator.capacity == 16384);
    verify(reader.buffer.allocator.position == 2048);
    verify(reader.buffer.begin == 7048);
    verify(strneq(result, sock, lengthof(sock)));


  success();
    io_close(&reader);
}
