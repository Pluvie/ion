spec( list_at ) {

  argument(list<int>* list);
  argument(int position);

  precondition("a non-negative position");
    #define valid_position_precondition \
      position = 3;

  when("the list is stack allocated") {
    #define stack_allocated_list_condition \
      list<int> stack_list = list_init(int, 16); \
      list = &stack_list;

    and_when("the list length is greater than the position") {
      #define list_length_condition \
        list_push(list, 1); \
        list_push(list, 2); \
        list_push(list, 3); \
        list_push(list, 4); \
        list_push(list, 5);

      apply(valid_position_precondition);
      apply(stack_allocated_list_condition);
      apply(list_length_condition);

      int* result = list_at(list, position);

      must("not fail");
        verify(error.occurred == false);

      must("return the element at the specified position");
        verify(*result == 4);

      success();

      #undef list_length_condition
    }

    and_when("the list length is lesser or equal than the position") {
      #define list_length_condition \
        list_push(list, 1); \
        list_push(list, 2); \
        list_push(list, 3);

      apply(valid_position_precondition);
      apply(stack_allocated_list_condition);
      apply(list_length_condition);

      int* result = list_at(list, position);

      must("fail with a specific error");
        verify(error.occurred == true);
        verify(streq(error.message, "3: overbound list position"));

      must("return NULL");
        verify(result == NULL);

      success();

      #undef list_length_condition
    }

    #undef stack_allocated_list_condition
  }

  when("the list is heap allocated") {
    #define heap_allocated_list_condition \
      list = list_alloc(int, 16, spec_allocator);

    and_when("the list length is greater than the position") {
      #define list_length_condition \
        list_push(list, 1); \
        list_push(list, 2); \
        list_push(list, 3); \
        list_push(list, 4); \
        list_push(list, 5);

      apply(valid_position_precondition);
      apply(heap_allocated_list_condition);
      apply(list_length_condition);

      int* result = list_at(list, position);

      must("not fail");
        verify(error.occurred == false);

      must("return the element at the specified position");
        verify(*result == 4);

      success();

      #undef list_length_condition
    }

    and_when("the list length is lesser or equal than the position") {
      #define list_length_condition \
        list_push(list, 1); \
        list_push(list, 2); \
        list_push(list, 3);

      apply(valid_position_precondition);
      apply(heap_allocated_list_condition);
      apply(list_length_condition);

      int* result = list_at(list, position);

      must("fail with a specific error");
        verify(error.occurred == true);
        verify(streq(error.message, "3: overbound list position"));

      must("return NULL");
        verify(result == NULL);

      success();

      #undef list_length_condition
    }

    #undef heap_allocated_list_condition
  }

  #undef valid_position_precondition
}
