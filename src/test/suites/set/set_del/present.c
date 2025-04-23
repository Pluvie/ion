test( set_del, present ) {

  given("a declined set");
    memory allocator = memory_init(0);
    set(string) set = set_init(string)(0, &allocator);


  when("the set has some elements in it");
    set_add(string)(&set, &s("Alpha"));
    set_add(string)(&set, &s("Beta"));
    set_add(string)(&set, &s("Gamma"));
    verify(set.length == 3);


  when("an element is requested at a specific element which is present in the set");
    string element = s("Alpha");


  calling("set_del()");
    string* deleted_element = set_del(string)(&set, &element);


  must("return the deleted element and decrease the set length");
    verify(deleted_element != NULL);
    verify(streq(*deleted_element, s("Alpha")));
    verify(set.length == 2);


  success();
    memory_release(&allocator);
}
