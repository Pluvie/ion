test( protocol_failure, with_path ) {

  given("a protocol");
    struct protocol proto = { .error = &(struct failure) { 0 } };
    struct { struct string* name; u64 index; } path_node = { 0 };


  when("an allocator is given to the protocol");
    struct memory allocator = memory_init(4096);
    proto.allocator = &allocator;


  when("the protocol path has some nodes");
    struct array path = array_init(sizeof(path_node), 0, proto.allocator);
    proto.path = &path;

    path_node.name = &s("first");
    array_push(&path, &path_node);

    path_node.name = &s("second");
    path_node.index = 7;
    array_push(&path, &path_node);

    path_node.name = &s("third");
    path_node.index = 0;
    array_push(&path, &path_node);


  calling("protocol_failure()");
    protocol_failure(&proto, "%s: %i", "example", 9);


  must("record successfully the failure with the path");
    verify(proto.error->occurred == true);
    verify(streq(proto.error->message, "[first.7.third] example: 9"));


  success();
    memory_release(&allocator);
}
