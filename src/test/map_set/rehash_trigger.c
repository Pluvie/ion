test( map_set, rehash_trigger ) {

  given("a map");
    map<int, int>* map = map_alloc(int, int, 16, test_allocator);
    void* original_map_data = map->keys.data;
    int load_limit = map->keys.load_limit;


  when("the map has some elements in it, under the load limit");
    for (int index = 0; index < load_limit; index++)
      map_set(map, index, index * 2);


  when("adding a new element and surpassing the load limit");
    int element = 999;


  calling("map_set()");
    map_set(map, element, element * 2);


  must("trigger the map rehash");
    verify(map->keys.data != original_map_data);
    verify(map->length == load_limit + 1);
    verify(*map_get(map, element) == 999 * 2);


  success();
}
