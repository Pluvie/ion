test( io_read_descriptor, cursor_advance_partial ) {

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


  when("the descriptor read returns less bytes than the requested amount");
  calling("io_read_descriptor()");
    string result = io_read_descriptor(&io, 64, buffer);


  must("perform a read on the descriptor and advance the io cursor");
    verify(error.occurred == false);
    verify(streq(result, "1111111122222222333333334444444455555555\n"));
    verify(io.read_amount == 41);
    verify(io.reads_count == 1);
    verify(io.cursor.position == 41);


  success();
    io_close(&io);
    close(desc);
}
