test( io_open, autocalc_length ) {

  given("a file descriptor");
    int desc = open("src/test/io/io_macro.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    verify(desc >= 0);


  calling("io_open() with a 0 length");
    struct io io = io_open(IO_DESCRIPTOR, desc, 0);


  must("calculate automatically the length of the descriptor");
    verify(error.occurred == false);
    verify(io.length == 62);


  success();
    io_close(&io);
    close(desc);
}
