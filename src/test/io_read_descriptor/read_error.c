test( io_read_descriptor, read_error ) {

  given("a file descriptor");
    int32 pipes[2];
    verify(pipe(pipes) == 0);


  given("an io over that descriptor");
    struct io io = io_open(IO_DESCRIPTOR, pipes[0], 0);
    verify(io.cursor.position == 0);
    verify(io.read_amount == 0);
    verify(io.reads_count == 0);


  given("a data buffer");
    char buffer[1024] = { 0 };


  when("the descriptor read returns less bytes than the requested amount");
    /* We are setting the non blocking flag in the descriptor, which, since is a
     * pipe with no data on it, shall immediately return with EAGAIN errno, and thus
     * simulating a `read` error. */
    fcntl(pipes[0], F_SETFL, O_NONBLOCK);


  calling("io_read_descriptor()");
    string result = io_read_descriptor(&io, 32, buffer);


  must("fail to read on the descriptor with a specific error");
    verify(error.occurred == true);
    verify(error_is("descriptor read error: Resource temporarily unavailable"));
    verify(error.code == EAGAIN);
    verify(strnull(result));
    verify(result.length == 0);
    verify(io.read_amount == 0);
    verify(io.reads_count == 0);
    verify(io.cursor.position == 0);


  success();
    io_close(&io);
    close(pipes[0]);
    close(pipes[1]);
}
