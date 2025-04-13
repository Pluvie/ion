test( map_get, string_keys ) {

  given("a declined map");
    memory allocator = memory_init(0);
    map(string, string) m = map_init(string, string)(0, &allocator);


  when("the map has some keys in it");
    map_set(string, string)(&m, &s("Mercury"),  &s("Rocky"));
    map_set(string, string)(&m, &s("Venus"),    &s("Rocky"));
    map_set(string, string)(&m, &s("Earth"),    &s("Rocky"));
    map_set(string, string)(&m, &s("Mars"),     &s("Rocky"));
    map_set(string, string)(&m, &s("Jupiter"),  &s("Gas Giant"));
    map_set(string, string)(&m, &s("Saturn"),   &s("Gas Giant"));
    map_set(string, string)(&m, &s("Uranus"),   &s("Gas Giant"));
    map_set(string, string)(&m, &s("Neptune"),  &s("Gas Giant"));
    map_set(string, string)(&m, &s("Pluto"),    &s("Rocky"));


  when("an element is requested at a specific key");
    string planet = s("Saturn");


  calling("map_get()");
    string* surface = map_get(string, string)(&m, &planet);


  must("return the correct element at that key");
    verify(surface != NULL);
    verify(streq(*surface, s("Gas Giant")));


  success();
    memory_release(&allocator);
}
