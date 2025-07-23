spec( set ) {

  precondition("a valid element type");
    #define valid_element_type  char*

  precondition("a valid list of elements of that type")
    #define valid_elements { \
      "Jane Shepard", \
      "Garrus Vakarian", \
      "Liara T'Soni", \
    }

  must("create a frozen stack allocated set of the given elements");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    set<char*> squad = set(valid_element_type, valid_elements);

    verify((void*) squad.data >= stack_begin);
    verify((void*) squad.data <= stack_end);
    verify(squad.allocator == NULL);
    verify(squad.capacity == 3);
    verify(squad.length == 3);

  success();

  #undef valid_element_type
  #undef valid_elements
}
