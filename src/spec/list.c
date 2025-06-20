spec( list ) {

  precondition("a valid type");
    #define valid_type struct squadmate

  precondition("a valid list of elements of that type")
    #define valid_elements { \
      { s("Jane Shepard"), SOLDIER, 800, 400 }, \
      { s("Garrus Vakarian"), INFILTRATOR, 600, 600 }, \
      { s("Liara T'Soni"), ADEPT, 200, 800 }, \
    }

  must("create a frozen stack allocated list of the given elements");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    list<struct squadmate> squad = list(valid_type, valid_elements);

    verify((void*) squad.data >= stack_begin);
    verify((void*) squad.data <= stack_end);
    verify(squad.allocator == NULL);
    verify(squad.capacity == 3);
    verify(squad.length == 3);

  success();

  #undef valid_type
  #undef valid_elements
}
