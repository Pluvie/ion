test( io_buffer_read, extend ) {

  given("an io");
    string data = s("1111111122222222333333334444444455555555");
    struct io io = io(IO_MEMORY, data.content, data.length);


  when("the io buffer has read some data, and has still some available space");
    void* buffer_data = malloc(16);
    io.buffer.size = 16;
    io.buffer.data = buffer_data;
    memcpy(io.buffer.data, data.content, 16);
    io.buffer.capacity = 16;
    io.buffer.end = 15;
    io.buffer.cursor = 15;
    io.cursor.position = 15;


  when("an amount that does not fit into the buffer available space is asked to be read");
    int amount = 4;


  calling("io_buffer_read()");
    string result = io_buffer_read(&io, amount);


  must("extend the buffer and read the data from the channel");
    verify(error.occurred == false);
    verify(streq(result, "2333"));
    verify(result.length == 4);
    verify(io.read_amount == 16);
    verify(io.reads_count == 1);
    verify(io.cursor.position == 19);
    verify(io.buffer.data != buffer_data);
    verify(io.buffer.capacity == 31);
    verify(io.buffer.end == 19);
    verify(io.buffer.cursor == 19);


  success();
    io_buffer_release(&io);
    io_close(&io);
}
