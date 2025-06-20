test( list_init, stack_allocated ) {

  given("a list");
    list<int> list;


  calling("list_init()");
    list = list_init(int, 8);


  must("initialize the list on the stack with corresponding capacity");
    verify(list.allocator == NULL);
    verify(list.length == 0);
    verify(list.capacity == 8);


  success();
}
