test( map_has, not_present ) {

  given("a declined map");
    map(string, string) map = map_init(string, string)(0, test_allocator);


  when("the map has some keys in it");
    map_set(string, string)(&map, &s("Alpha"), &s("Greek"));
    map_set(string, string)(&map, &s("Beta"), &s("Greek"));
    map_set(string, string)(&map, &s("Gamma"), &s("Greek"));


  when("an element is requested at a specific key which is not present in the map");
    string key = s("Delta");


  calling("map_has()");
    bool present = map_has(string, string)(&map, &key);


  must("return true");
    verify(present == false);


  success();
}
