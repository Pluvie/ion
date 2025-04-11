test( map_rehash, doubled_capacity ) {

  given("a declined map");
    memory allocator = memory_init(0);
    map(i32, i32) m = map_init(i32, i32)(0, &allocator);
    u64 original_capacity = m.capacity;


  when("the map has some keys in it");
    for (i32 index = 0; index < 3; index++)
      map_set(i32, i32)(&m, &index, &index);


  calling("map_rehash()");
    map_rehash(i32, i32)(&m);


  must("double the map capacity");
    verify(m.capacity == 2 * original_capacity);


  success();
    memory_release(&allocator);
}
