test( set_has, present ) {

  given("a declined set");
    set(string) set = set_init(string)(0, test_allocator);


  when("the set has some elements in it");
    set_add(string)(&set, &s("Alpha"));
    set_add(string)(&set, &s("Beta"));
    set_add(string)(&set, &s("Gamma"));


  when("an element is requested at a specific element which is present in the set");
    string element = s("Alpha");


  calling("set_has()");
    bool present = set_has(string)(&set, &element);


  must("return true");
    verify(present == true);


  success();
}
