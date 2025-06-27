spec( list_pop ) {

  argument(list<int>* list);

  when("the list is stack allocated") {
    #define stack_allocated_list_condition \
      list<int> stack_list = list_init(int, 16); \
      list = &stack_list;

    and_when("the list has at least one element") {
      #define list_not_empty_condition \
        list_push(list, 7); \
        list_push(list, 8); \
        list_push(list, 9);

      apply(stack_allocated_list_condition);
      apply(list_not_empty_condition);

      int original_list_length = list->length;
      int original_list_capacity = list->capacity;

      int* result = list_pop(list);

      must("not fail");
        verify(error.occurred == false);

      must("decrease the list length by 1");
        verify(list->length == original_list_length - 1);

      must("return the element at the position equal to the list length");
        verify(*result == 9);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();

      #undef list_not_empty_condition
    }

    and_when("the list has no elements") {
      #define empty_list_condition \
        list->length = 0;

      apply(stack_allocated_list_condition);
      apply(empty_list_condition);

      int original_list_capacity = list->capacity;

      int* result = list_pop(list);

      must("fail with a specific error");
        verify(error.occurred == true);
        verify(streq(error.message, "pop: empty list"));

      must("return NULL");
        verify(result == NULL);

      must("leave the list at 0 length");
        verify(list->length == 0);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();

      #undef empty_list_condition
    }

    #undef stack_allocated_list_condition
  }

  when("the list is heap allocated") {
    #define heap_allocated_list_condition \
      list = list_alloc(int, 16, spec_allocator);

    and_when("the list has at least one element") {
      #define list_not_empty_condition \
        list_push(list, 7); \
        list_push(list, 8); \
        list_push(list, 9);

      apply(heap_allocated_list_condition);
      apply(list_not_empty_condition);

      int original_list_length = list->length;
      int original_list_capacity = list->capacity;

      int* result = list_pop(list);

      must("not fail");
        verify(error.occurred == false);

      must("decrease the list length by 1");
        verify(list->length == original_list_length - 1);

      must("return the element at the position equal to the list length");
        verify(*result == 9);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();

      #undef list_not_empty_condition
    }

    and_when("the list has no elements") {
      #define empty_list_condition \
        list->length = 0;

      apply(heap_allocated_list_condition);
      apply(empty_list_condition);

      int original_list_capacity = list->capacity;

      int* result = list_pop(list);

      must("fail with a specific error");
        verify(error.occurred == true);
        verify(streq(error.message, "pop: empty list"));

      must("return NULL");
        verify(result == NULL);

      must("leave the list at 0 length");
        verify(list->length == 0);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();

      #undef empty_list_condition
    }

    #undef heap_allocated_list_condition
  }
}
