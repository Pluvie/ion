test( map_each, avoid_empty ) {

  given("a declined map");
    memory allocator = memory_init(0);
    map(string, string) m = map_init(string, string)(0, &allocator);


  when("the map has some keys in it");
    map_set(string, string)(&m, &s("Mercury"),  &s("Solar System"));
    map_set(string, string)(&m, &s("Venus"),    &s("Solar System"));
    map_set(string, string)(&m, &s("Earth"),    &s("Solar System"));
    map_set(string, string)(&m, &s("Mars"),     &s("Solar System"));
    map_set(string, string)(&m, &s("Jupiter"),  &s("Solar System"));
    map_set(string, string)(&m, &s("Saturn"),   &s("Solar System"));
    map_set(string, string)(&m, &s("Neptune"),  &s("Solar System"));
    map_set(string, string)(&m, &s("Uranus"),   &s("Solar System"));
    map_set(string, string)(&m, &s("Pluto"),    &s("Solar System"));


  calling("map_each()");
  must("loop over the keys and values of the map, avoiding the empty spots");
    map_(iterator, string, string) iter = { 0 };
    for map_each(&m, iter)
      verify(streq(*iter.value, s("Solar System")));
    verify(iter.index == 9);


  success();
    memory_release(&allocator);
}
