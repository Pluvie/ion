test( map_del, decrease_length ) {

  given("a map");
    map<int, int>* map = map_alloc(int, int, 16, test_allocator);
    map_set(map, 7, 49);
    map_set(map, 8, 64);
    map_set(map, 9, 81);
    verify(map->length == 3);


  when("an element is present in the map");
    int element = 9;


  calling("map_del()");
    int* deleted_element = map_del(map, element);


  must("decrease the map length");
    verify(*deleted_element == 81);
    verify(map->length == 2);


  success();
}
