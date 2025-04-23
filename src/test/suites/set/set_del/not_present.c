test( set_del, not_present ) {

  given("a declined set");
    set(string) set = set_init(string)(0, test_allocator);


  when("the set has some elements in it");
    set_add(string)(&set, &s("Alpha"));
    set_add(string)(&set, &s("Beta"));
    set_add(string)(&set, &s("Gamma"));
    verify(set.length == 3);


  when("an element is requested at a specific element which is not present in the set");
    string element = s("Delta");


  calling("set_del()");
    string* deleted_element = set_del(string)(&set, &element);


  must("return NULL and not decrease the set length");
    verify(deleted_element == NULL);
    verify(set.length == 3);


  success();
}
