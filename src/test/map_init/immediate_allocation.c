test( map_init, immediate_allocation ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);


  calling("map_init()");
    map = map_init(sizeof(u64), sizeof(u64), 0, &allocator);


  must("initialize the map and immediately allocate its memory");
    verify(map.capacity > 0);
    verify(allocator.data != NULL);


  success();
    memory_release(&allocator);
}
