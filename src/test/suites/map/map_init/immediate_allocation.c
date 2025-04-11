test( map_init, immediate_allocation ) {

  given("a declined map");
    map(i32, i32) m;
    memory allocator = memory_init(0);


  calling("map_init()");
    m = map_init(i32, i32)(0, &allocator);


  must("initialize the map and immediately allocate its memory");
    verify(m.capacity > 0);
    verify(allocator.data != NULL);


  success();
    memory_release(&allocator);
}
