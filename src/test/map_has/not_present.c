test( map_has, not_present ) {

  given("a map");
    map<int, int> map = map(int, int, {
      { 7, 49 },
      { 8, 64 },
      { 9, 81 },
    });


  when("an element is not present in the map");
    int element = 5;


  calling("map_has()");
    bool presence = map_has(&map, element);


  must("return false");
    verify(presence == false);


  success();
}
