test( map_rehash, data_invariance ) {

  given("a declined map");
    memory allocator = memory_init(0);
    map(i32, i32) m = map_init(i32, i32)(0, &allocator);


  when("the map has some keys in it");
    for (i32 index = 0; index < 3; index++)
      map_set(i32, i32)(&m, &index, &index);


  calling("map_rehash()");
    map_rehash(i32, i32)(&m);


  must("be invariant on keys and values");
    for (i32 index = 0; index < 3; index++)
      verify(as(i32, map_get(i32, i32)(&m, &index)) == index);


  success();
    memory_release(&allocator);
}
