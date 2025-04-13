test( set_add, increase_length ) {

  given("a declined set");
    memory allocator = memory_init(0);
    set(string) s = set_init(string)(0, &allocator);
    verify(s.length == 0);


  when("adding a new element");
    string element = s("Hello");


  calling("set_add()");
    set_add(string)(&s, &element);


  must("increase the set length");
    verify(s.length == 1);


  success();
    memory_release(&allocator);
}
