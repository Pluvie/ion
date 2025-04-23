test( map_each, avoid_empty ) {

  given("a declined map");
    map(string, string) map = map_init(string, string)(0, test_allocator);


  when("the map has some keys in it");
    map_set(string, string)(&map, &s("Mercury"),  &s("Solar System"));
    map_set(string, string)(&map, &s("Venus"),    &s("Solar System"));
    map_set(string, string)(&map, &s("Earth"),    &s("Solar System"));
    map_set(string, string)(&map, &s("Mars"),     &s("Solar System"));
    map_set(string, string)(&map, &s("Jupiter"),  &s("Solar System"));
    map_set(string, string)(&map, &s("Saturn"),   &s("Solar System"));
    map_set(string, string)(&map, &s("Uranus"),   &s("Solar System"));
    map_set(string, string)(&map, &s("Neptune"),  &s("Solar System"));
    map_set(string, string)(&map, &s("Pluto"),    &s("Solar System"));


  calling("map_each()");
  must("loop over the keys and values of the map, avoiding the empty spots");
    map_iterator(string, string) iter = { 0 };
    for map_each(&map, iter)
      verify(streq(*iter.value, s("Solar System")));
    verify(iter.index == 9);


  success();
    memory_release(test_allocator);
}
