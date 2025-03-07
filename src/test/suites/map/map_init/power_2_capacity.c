test( map_init, power_2_capacity ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);


  when("providing a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("map_init()");
    map = map_init(sizeof(u64), sizeof(u64), capacity, &allocator);


  must("initialize the map with the next power of 2 capacity");
    verify(map.capacity == 128);


  success();
    memory_release(&allocator);
}
