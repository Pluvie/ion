test( map_init, power_2_capacity ) {

  given("a declined map");
    map(i32, i32) map;


  when("providing a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("map_init()");
    map = map_init(i32, i32)(capacity, test_allocator);


  must("initialize the map with the next power of 2 capacity");
    verify(map.capacity == 128);


  success();
}
