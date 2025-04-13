test( map_has, not_present ) {

  given("a declined map");
    memory allocator = memory_init(0);
    map(string, string) m = map_init(string, string)(0, &allocator);


  when("the map has some keys in it");
    map_set(string, string)(&m, &s("Alpha"), &s("Greek"));
    map_set(string, string)(&m, &s("Beta"), &s("Greek"));
    map_set(string, string)(&m, &s("Gamma"), &s("Greek"));


  when("an element is requested at a specific key which is not present in the map");
    string key = s("Delta");


  calling("map_has()");
    bool present = map_has(string, string)(&m, &key);


  must("return true");
    verify(present == false);


  success();
    memory_release(&allocator);
}
