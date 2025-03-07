test( io_read_socket, buffered_retention ) {

  given("a socket");
    char sock[4096] = { 0 };
    memset(sock, 'f', lengthof(sock));
    recv_simulated_data = &io_open_memory(sock, lengthof(sock));


  when("a struct io is opened on that socket");
    struct io reader = io_open_socket(0);


  calling("io_read()");
    char result[lengthof(sock)];
    for (u32 i = 0; i < lengthof(sock); i++)
      result[i] = *(char*) io_read(&reader, 1);


  must("do a buffered read of the io");
    verify(recv_simulated_data->reads_count == 4);
    verify(reader.reads_count == lengthof(sock));
    verify(reader.buffer.allocator.capacity == 4*reader.buffer.size);
    verify(reader.buffer.allocator.position == 2*reader.buffer.size);
    verify(reader.buffer.begin == 2*reader.buffer.size);
    verify(strneq(result, sock, lengthof(sock)));


  success();
    io_close(&reader);
}
