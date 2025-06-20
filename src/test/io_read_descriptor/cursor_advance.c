test( io_read_descriptor, cursor_advance ) {

  given("a file descriptor");
    int desc = open("src/test/io_read_descriptor/descriptor.txt",
      O_RDONLY, S_IRUSR | S_IWUSR);
    verify(desc >= 0);


  given("an io over that descriptor");
    struct io io = io_open(IO_DESCRIPTOR, desc, 0);
    verify(io.cursor.position == 0);
    verify(io.read_amount == 0);
    verify(io.reads_count == 0);


  given("a data buffer");
    char buffer[1024] = { 0 };


  calling("io_read_descriptor()");
    string result = io_read_descriptor(&io, 32, buffer);


  must("perform a read on the descriptor and advance the io cursor");
    verify(error.occurred == false);
    verify(streq(result, "11111111222222223333333344444444"));
    verify(io.read_amount == 32);
    verify(io.reads_count == 1);
    verify(io.cursor.position == 32);


  success();
    io_close(&io);
    close(desc);
}
