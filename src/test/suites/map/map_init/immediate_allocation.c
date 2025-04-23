test( map_init, immediate_allocation ) {

  given("a declined map");
    map(i32, i32) map;
    verify(test_allocator->data == NULL);


  calling("map_init()");
    map = map_init(i32, i32)(0, test_allocator);


  must("initialize the map and immediately allocate its memory");
    verify(map.capacity > 0);
    verify(test_allocator->data != NULL);


  success();
}
