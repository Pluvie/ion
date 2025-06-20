test( set_init, stack_allocated ) {

  given("a set");
    set<int> set;


  calling("set_init()");
    set = set_init(int, 8);


  must("initialize the set on the stack with corresponding capacity");
    verify(set.allocator == NULL);
    verify(set.length == 0);
    verify(set.capacity == 8);


  success();
}
