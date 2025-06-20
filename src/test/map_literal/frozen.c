test( map_literal, frozen ) {

  calling("map_literal()");
    map<int, int> map = map(int, int, {
      { 7, 49 },
      { 8, 64 },
      { 9, 81 },
    });


  must("create a frozen map literal");
    verify(map.length == 3);
    verify(map.keys.length == map.keys.capacity);
    verify(map.keys.length == map.keys.load_limit);
    verify(*map_get(&map, 7) == 49);
    verify(*map_get(&map, 8) == 64);
    verify(*map_get(&map, 9) == 81);


  success();
}
