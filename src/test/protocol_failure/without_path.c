test( protocol_failure, without_path ) {

  given("a protocol");
    struct protocol proto = { .error = &(struct failure) { 0 } };


  when("an allocator is given to the protocol");
    struct memory allocator = memory_init(4096);
    proto.allocator = &allocator;


  when("the protocol path is empty");
    proto.path = NULL;


  calling("protocol_failure()");
    protocol_failure(&proto, "%s: %i", "example", 9);


  must("record successfully the failure without the path");
    verify(proto.error->occurred == true);
    verify(streq(proto.error->message, "example: 9"));


  success();
    memory_release(&allocator);
}
