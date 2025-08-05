spec( io_buffer_init ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io with buffer enabled but not initialized");
  precondition("the underlying channel has some data available to read");
    #define preconditions(channel_available_data) \
      string data = s("1111111122222222333333334444444455555555"); \
      struct pipe channel; pipe_open(&channel); \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(channel.reader); \
      io->buffer.enabled = true; \
      io->buffer.size = 8; \
      io->buffer.data = NULL; \
      write(channel.writer, data.content, channel_available_data);

  when("the buffer size is negative or zero") {
    apply(preconditions(8));
    io->buffer.size = -10;
    io_buffer_init(io, 8);

    must("force the buffer size to 1024");
      verify(io->buffer.size == 1024);

    success();
      io_close(io);
      pipe_close(&channel);
  } end();

  when("the buffer size is positive") {
    when("the amount to read is greater than the buffer size") {
      amount = 12;

      when("the underlying channel contains less data than the amount to read") {
        int channel_available_data = amount - 5;
        apply(preconditions(channel_available_data));
        /*        ┌────────────────────────────────────────┐
          channel:│1111111                                 │
                  └────────────────────────────────────────┘
          amount:  ■■■■■■■■■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_init(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("allocate buffer data equal to the channel available data");
          verify(io->buffer.end == channel_available_data);
        must("read data from the io channel");
          verify(io->read.count == 1);
        must("advance the buffer cursor by a quantity equal to the available data "\
             "on the channel");
          verify(io->buffer.cursor == channel_available_data);
        must("return a slice of data with length equal to the available data on "\
             "the channel");
          verify(result.length == channel_available_data);
          verify(streq(result, "1111111"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();

      when("the underlying channel contains equal or more data than the amount to read") {
        int channel_available_data = amount + 12;
        apply(preconditions(channel_available_data));
        /*        ┌────────────────────────────────────────┐
          channel:│111111112222222233333333                │
                  └────────────────────────────────────────┘
          amount:  ■■■■■■■■■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_init(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("allocate buffer data equal to the buffer size plus the amount to read");
          verify(io->buffer.end == io->buffer.size + amount);
        must("read data from the io channel");
          verify(io->read.count == 1);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "111111112222"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();
    } end();

    when("the amount to read is lesser or equal than the buffer size") {
      amount = 4;

      when("the underlying channel contains less data than the amount to read") {
        int channel_available_data = amount - 1;
        apply(preconditions(channel_available_data));
        /*        ┌────────────────────────────────────────┐
          channel:│111                                     │
                  └────────────────────────────────────────┘
          amount:  ■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_init(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("allocate buffer data equal to the channel available data");
          verify(io->buffer.end == channel_available_data);
        must("read data from the io channel");
          verify(io->read.count == 1);
        must("advance the buffer cursor by a quantity equal to the available data "\
             "on the channel");
          verify(io->buffer.cursor == channel_available_data);
        must("return a slice of data with length equal to the available data on "\
             "the channel");
          verify(result.length == channel_available_data);
          verify(streq(result, "1111111"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();

      // when("the io buffer is not initialized")
      // when("the amount to read is lesser or equal than the buffer size")
      when("the underlying channel contains equal or more data than the amount to read") {
        int channel_available_data = amount + 12;
        apply(preconditions(channel_available_data));
        /*        ┌────────────────────────────────────────┐
          channel:│1111111122222222                        │
                  └────────────────────────────────────────┘
          amount:  ■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_init(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("allocate buffer data equal to the buffer size");
          verify(io->buffer.end == io->buffer.size);
        must("read data from the io channel");
          verify(io->read.count == 1);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "1111111"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();
    } end();
  } end();

  #undef preconditions
}
