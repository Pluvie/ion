test( map_init, default_capacity ) {

  given("a declined map");
    map(i32, i32) m;
    memory allocator = memory_init(0);


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("map_init()");
    m = map_init(i32, i32)(capacity, &allocator);


  must("initialize the map with #MAP_CAPACITY_DEFAULT capacity");
    verify(m.capacity == MAP_CAPACITY_DEFAULT);


  success();
    memory_release(&allocator);
}
