test( map_has, present ) {

  given("a map");
    map<int, int> map = map(int, int, {
      { 7, 49 },
      { 8, 64 },
      { 9, 81 },
    });


  when("an element is present in the map");
    int element = 8;


  calling("map_has()");
    bool presence = map_has(&map, element);


  must("return true");
    verify(presence == true);


  success();
}
