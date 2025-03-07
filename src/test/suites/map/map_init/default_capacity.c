test( map_init, default_capacity ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("map_init()");
    map = map_init(sizeof(u64), sizeof(u64), capacity, &allocator);


  must("initialize the map with #MAP_DEFAULT_CAP capacity");
    verify(map.capacity == MAP_DEFAULT_CAP);


  success();
    memory_release(&allocator);
}
