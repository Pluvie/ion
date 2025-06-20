test( io, io_macro ) {

  given("a file descriptor");
    int desc = open("src/test/io/io_macro.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    verify(desc >= 0);


  given("a socket descriptor");
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    verify(sock >= 0);


  given("a memory pointer");
    void* mem = memory_alloc_zero(test_allocator, 16);
    verify(mem != NULL);


  given("a file stream");
    void* stream = fopen("src/test/io/io_macro.txt", "r");
    verify(stream != NULL);


  calling("the io macro");
    struct io io_desc = io(IO_DESCRIPTOR, desc);
    struct io io_sock = io(IO_SOCKET, sock);
    struct io io_mem = io(IO_MEMORY, mem);
    struct io io_stream = io(IO_STREAM, stream);


  must("initialize io with the correct parameters");
    verify(error.occurred == false);
    verify(io_desc.channel == IO_DESCRIPTOR);
    verify(io_desc.descriptor == desc);
    verify(io_sock.channel == IO_SOCKET);
    verify(io_sock.socket == sock);
    verify(io_mem.channel == IO_MEMORY);
    verify(io_mem.memory == mem);
    verify(io_stream.channel == IO_STREAM);
    verify(io_stream.stream == stream);


  success();
    close(desc);
    close(sock);
    fclose(stream);
}
