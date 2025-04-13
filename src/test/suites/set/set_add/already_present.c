test( set_add, already_present ) {

  given("a declined set");
    memory allocator = memory_init(0);
    set(string) s = set_init(string)(0, &allocator);


  when("the set has some elements in it");
    set_add(string)(&s, &s("Hello"));
    set_add(string)(&s, &s("World"));
    verify(s.length == 2);


  when("adding an element which is already present in the set");
    string element = s("Hello");


  calling("set_add()");
    set_add(string)(&s, &element);


  must("not increase the set length");
    verify(s.length == 2);


  success();
    memory_release(&allocator);
}
