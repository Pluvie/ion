test( set_has, present ) {

  given("a declined set");
    memory allocator = memory_init(0);
    set(string) s = set_init(string)(0, &allocator);


  when("the set has some elements in it");
    set_add(string)(&s, &s("Alpha"));
    set_add(string)(&s, &s("Beta"));
    set_add(string)(&s, &s("Gamma"));


  when("an element is requested at a specific element which is present in the set");
    string element = s("Alpha");


  calling("set_has()");
    bool present = set_has(string)(&s, &element);


  must("return true");
    verify(present == true);


  success();
    memory_release(&allocator);
}
