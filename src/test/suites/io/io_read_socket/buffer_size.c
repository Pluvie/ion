test( io_read_socket, buffer_size ) {

  given("a socket");
    char sock[8192] = { 0 };
    memset(sock, 'f', lengthof(sock));
    recv_simulated_data = &io_open_memory(sock, lengthof(sock));


  when("a struct io is opened on that socket");
    struct io reader = io_open_socket(0);


  when("the buffer of the io is set to a higher amount");
    reader.buffer.size = 8000;


  calling("io_read()");
    char result[lengthof(sock)];
    u32 reads_count = 0;
    for(u32 cursor = 0; cursor < lengthof(sock); cursor++) {
      result[cursor] = *(char*) io_read(&reader, 1);
      reads_count++;
    }


  must("reduce the number of system calls");
    verify(recv_simulated_data->reads_count == 2);
    verify(reader.reads_count == reads_count);
    verify(reader.buffer.allocator.capacity == 16384);
    verify(reader.buffer.allocator.position == 8191);
    verify(reader.buffer.begin == 0);
    verify(strneq(result, sock, reader.length));


  success();
    io_close(&reader);
}
