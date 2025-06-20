spec( io_buffer_compact ) {

  argument(struct io* io);

  precondition("the io has an already initialized buffer and with a cursor greater "
      "than the io buffer size");
    #define io_precondition \
      io = io(IO_STRING, s("1111111122222222333333334444444455555555")); \
      string initial_buffer = s("333344444444"); \
      io.buffer.data = malloc(initial_buffer.length); \
      memcpy(io.buffer.data, initial_buffer.content, initial_buffer.length); \
      io.buffer.size = 16; \
      io.buffer.end = 28; \
      io.buffer.capacity = 12; \
      io.buffer.cursor = 20;

  when("the io mode is IO_BUFFER_RETAIN") {
    /*
              ┌────────────────────────────────────────┐
      io:     │1111111122222222333333334444444455555555│
              └────────────────────────────────────────┘
      amount:                      ■■■■■■
              ┌────────────────────────────────────────┐
      buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒            │
              └────────────────────┬──────┬────────────┘
                                   ▼      ▼
                                cursor   end */

    amount = 6;
    apply(io_precondition);
    string result = io_buffer_read(&io, amount);

    must("not fail");
      verify(error.occurred == false);

    must("advance the io buffer cursor of the given amount");
      verify(io.buffer.cursor == 4 + amount);

    must("read the data from the buffer without performing any read from the io channel");
      verify(io.reads_count == 0);

    must("return a string of data of the given amount");
      verify(result.length == amount);
      verify(streq(result, "111122"));

    io_close(io);
  }

  when("the io mode is not IO_BUFFER_RETAIN") {
    /*
              ┌────────────────────────────────────────┐
      io:     │1111111122222222333333334444444455555555│
              └────────────────────────────────────────┘
      amount:                      ■■■■■■
              ┌────────────────────────────────────────┐
      buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒            │
              └────────────────────┬──────┬────────────┘
                                   ▼      ▼
                                cursor   end */

    amount = 6;
    apply(io_precondition);
    string result = io_buffer_read(&io, amount);

    must("not fail");
      verify(error.occurred == false);

    must("advance the io buffer cursor of the given amount");
      verify(io.buffer.cursor == 4 + amount);

    must("not delete any data from the head of the buffer");
      verify(io.buffer.data == initial_buffer);

    must("return a string of data of the given amount");
      verify(result.length == amount);
      verify(streq(result, "111122"));

    io_close(io);
  }

  #undef io_precondition
}
