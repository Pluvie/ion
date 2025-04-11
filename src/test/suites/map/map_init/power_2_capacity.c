test( map_init, power_2_capacity ) {

  given("a declined map");
    map(i32, i32) m;
    memory allocator = memory_init(0);


  when("providing a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("map_init()");
    m = map_init(i32, i32)(capacity, &allocator);


  must("initialize the map with the next power of 2 capacity");
    verify(m.capacity == 128);


  success();
    memory_release(&allocator);
}
