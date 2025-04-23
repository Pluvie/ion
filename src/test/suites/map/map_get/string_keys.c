test( map_get, string_keys ) {

  given("a declined map");
    map(string, string) map = map_init(string, string)(0, test_allocator);


  when("the map has some keys in it");
    map_set(string, string)(&map, &s("Mercury"),  &s("Rocky"));
    map_set(string, string)(&map, &s("Venus"),    &s("Rocky"));
    map_set(string, string)(&map, &s("Earth"),    &s("Rocky"));
    map_set(string, string)(&map, &s("Mars"),     &s("Rocky"));
    map_set(string, string)(&map, &s("Jupiter"),  &s("Gas Giant"));
    map_set(string, string)(&map, &s("Saturn"),   &s("Gas Giant"));
    map_set(string, string)(&map, &s("Uranus"),   &s("Gas Giant"));
    map_set(string, string)(&map, &s("Neptune"),  &s("Gas Giant"));
    map_set(string, string)(&map, &s("Pluto"),    &s("Rocky"));


  when("an element is requested at a specific key");
    string planet = s("Saturn");


  calling("map_get()");
    string* surface = map_get(string, string)(&map, &planet);


  must("return the correct element at that key");
    verify(surface != NULL);
    verify(streq(*surface, s("Gas Giant")));


  success();
}
