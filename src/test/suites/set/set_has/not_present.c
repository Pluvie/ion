test( set_has, not_present ) {

  given("a declined set");
    memory allocator = memory_init(0);
    set(string) s = set_init(string)(0, &allocator);


  when("the set has some keys in it");
    set_add(string)(&s, &s("Alpha"));
    set_add(string)(&s, &s("Beta"));
    set_add(string)(&s, &s("Gamma"));


  when("an element is requested at a specific key which is not present in the set");
    string key = s("Delta");


  calling("set_has()");
    bool present = set_has(string)(&s, &key);


  must("return true");
    verify(present == false);


  success();
    memory_release(&allocator);
}
