test( set_add, increase_length ) {

  given("a declined set");
    set(string) set = set_init(string)(0, test_allocator);
    verify(set.length == 0);


  when("adding a new element");
    string element = s("Hello");


  calling("set_add()");
    set_add(string)(&set, &element);


  must("increase the set length");
    verify(set.length == 1);


  success();
}
