test( map_set, increase_length ) {

  given("a map");
    map<int, int> map = map_init(int, int, 16);


  calling("map_set()");
    map_set(&map, 1, 1);
    map_set(&map, 2, 4);
    map_set(&map, 3, 9);


  must("increase the map length");
    verify(map.length == 3);


  success();
}
