test( map_has, deleted ) {

  given("a map");
    map<int, int> map = map(int, int, {
      { 7, 49 },
      { 8, 64 },
      { 9, 81 },
    });


  when("an element is deleted from the map");
    int element = 8;
    map_del(&map, element);


  calling("map_has()");
    bool presence = map_has(&map, element);


  must("return false");
    verify(presence == false);


  success();
}
