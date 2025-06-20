spec( list_init ) {

  precondition("a valid type");
    #define valid_type int

  precondition("a greater than zero capacity")
    #define valid_capacity 8

  must("create an empty stack allocated list of the given capacity");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    list<int> list = list_init(valid_type, valid_capacity);

    verify((void*) list.data >= stack_begin);
    verify((void*) list.data <= stack_end);
    verify(list.allocator == NULL);
    verify(list.capacity == valid_capacity);
    verify(list.length == 0);

  success();

  #undef valid_type
  #undef valid_capacity
}
