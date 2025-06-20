test( map_del, invariance_on_missing ) {

  given("a map");
    map<int, int>* map = map_alloc(int, int, 16, test_allocator);
    map_set(map, 7, 49);
    map_set(map, 8, 64);
    map_set(map, 9, 81);
    verify(map->length == 3);


  when("an element is not present in the map");
    int element = 10;


  calling("map_del()");
    int* deleted_element = map_del(map, element);


  must("not change the map length");
    verify(deleted_element == NULL);
    verify(map->length == 3);


  success();
}
