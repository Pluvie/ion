test( io_read_socket, buffered_optimization ) {

  given("a socket");
    char* sock =
      "This socket contains sample data to simulate a long sequence of characters, "
      "which may be used by the struct io as parsing data for a language, data "
      "format, text, or other uses. The purpose of this lenghty sequence is to "
      "test the buffered read from socket, which optimizes the number of system "
      "calls by keeping a buffer window over the socket data.\n"
      "This works by reading an amount of bytes from the socket, and keeping it in "
      "the io `buffer` field: subsequent calls of `io_read` shall read from the "
      "buffer instead of the socket, thus reducing the number of system calls to "
      "`fread` and increasing io throughput speed.\n"
      "When the buffer is exhausted, or when a call to `io_read` exceeds the "
      "amount available in the buffer, another read is made from the socket in "
      "order to keep the buffer available ahead. Also, when the data behind starts "
      "to grow over the configured buffer sized, it shall be freed in order to "
      "reduce memory consumption.";
    recv_simulated_data = &io_open_memory(sock, strlen(sock));


  when("a struct io is opened on that socket");
    struct io reader = io_open_socket(0);


  calling("io_read() multiple times");
    char result[strlen(sock)];
    for (u32 i = 0; i < strlen(sock); i++)
      result[i] = *(char*) io_read(&reader, 1);


  must("do a buffered read of the io");
    verify(recv_simulated_data->reads_count == 1);
    verify(reader.reads_count == strlen(sock));
    verify(reader.buffer.allocator.capacity == 4*reader.buffer.size);
    verify(reader.buffer.allocator.position == strlen(sock));
    verify(reader.buffer.begin == 0);
    verify(strneq(result, sock, strlen(sock)));


  success();
    io_close(&reader);
}
