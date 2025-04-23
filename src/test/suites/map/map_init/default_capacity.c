test( map_init, default_capacity ) {

  given("a declined map");
    map(i32, i32) map;


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("map_init()");
    map = map_init(i32, i32)(capacity, test_allocator);


  must("initialize the map with #MAP_CAPACITY_DEFAULT capacity");
    verify(map.capacity == MAP_CAPACITY_DEFAULT);


  success();
}
