test( io_buffer_read, available_space ) {

  given("an io");
    string data = s("1111111122222222333333334444444455555555");
    struct io io = io(IO_MEMORY, data.content, data.length);


  when("the io buffer has read some data, and has still some available space");
    void* buffer_data = malloc(32);
    io.buffer.data = buffer_data;
    memcpy(io.buffer.data, data.content, 32);
    io.buffer.capacity = 32;
    io.buffer.end = 8;
    io.buffer.cursor = 8;
    io.cursor.position = 8;


  when("an amount that fits into the buffer available space is asked to be read");
    int amount = 8;


  calling("io_buffer_read()");
    string result = io_buffer_read(&io, amount);


  must("read back from the io channel and do not reallocate the buffer");
    verify(error.occurred == false);
    verify(streq(result, "222222222"));
    verify(result.length == 8);
    verify(io.read_amount == 8);
    verify(io.reads_count == 1);
    verify(io.cursor.position == 16);
    verify(io.buffer.data == buffer_data);
    verify(io.buffer.capacity == 32);
    verify(io.buffer.end == 16);
    verify(io.buffer.cursor == 16);


  success();
    io_buffer_release(&io);
    io_close(&io);
}
