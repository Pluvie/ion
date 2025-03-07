test( io_read_socket, buffer_size_overflow ) {

  given("a socket");
    char sock[8192] = { 0 };
    memset(sock, 'f', lengthof(sock));
    recv_simulated_data = &io_open_memory(sock, strlen(sock));


  when("a struct io is opened on that socket");
    struct io reader = io_open_socket(0);


  calling("io_read() with an amount greater than the buffer size");
    char* result = io_read(&reader, 16384);


  must("reduce the number of system calls");
    verify(recv_simulated_data->reads_count == 1);
    verify(reader.reads_count == 1);
    verify(reader.read_amount == lengthof(sock));
    verify(reader.buffer.allocator.capacity == 16384);
    verify(reader.buffer.allocator.position == lengthof(sock));
    verify(reader.buffer.begin == 0);
    verify(strneq(result, sock, lengthof(sock)));


  success();
    io_close(&reader);
}
