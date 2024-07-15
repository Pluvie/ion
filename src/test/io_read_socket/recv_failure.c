test( io_read_socket, recv_failure ) {

  given("a struct io");
    struct io reader = {
      .type = IO_TYPE_SOCK,
      .flags = IO_READ,
    };


  when("the reader has an allocator");
    struct memory allocator = memory_init(0);
    reader.allocator = &allocator;


  when("the recv call fails");
    recv_simulated_data = NULL;


  calling("io_read()");
    byte* value = io_read(&reader, 4);


  must("successfully read the io");
    verify(value == NULL);
    verify(reader.cursor == 0);
    verify(reader.length == 0);


  success();
    memory_release(&allocator);
}
