spec( json_discard_value ) {

  argument(struct io* io);

  precondition("a valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("the io is direct") {
    apply(preconditions);
    string content = s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } ");
    *io = io_open(&content, NULL, spec_allocator);

    struct squadmate shepard = { 0 };
    json_discard_value(io->direct);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      int parsed_length = io->direct->cursor - io->direct->data->pointer;
      verify(parsed_length == 43);
      verify(*io->direct->cursor == ' ');
    must("leave the target unchanged");
      verify(eq(&shepard, &(struct squadmate) { 0 }));

    success();
      io_close(io);
  } end();

  /*
  when("the io is buffered") {
  } end();
  */

  #undef preconditions
}
