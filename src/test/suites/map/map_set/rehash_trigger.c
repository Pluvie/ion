test( map_set, rehash_trigger ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);
    map = map_init(sizeof(u64), sizeof(u64), 8, &allocator);
    void* original_entries_address = map.entries;


  when("the map has some entries in it");
    for (u64 index = 0; index < 9; index++)
      map_set(&map, &index, &index);


  calling("map_set()");
    u64 key = 10;
    u64 value = 10;
    map_set(&map, &key, &value);


  must("trigger the map rehash");
    verify(original_entries_address != map.entries);


  success();
    memory_release(&allocator);
}
