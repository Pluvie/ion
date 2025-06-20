spec( list_push ) {

  argument(list<int>* list);
  argument(int element);

  precondition("a valid element")
    #define valid_element_precondition \
      element = 7;

  when("the list is stack allocated") {
    #define stack_allocated_list_condition \
      list<int> stack_list = list_init(int, 16); \
      list = &stack_list;

    when("the list length is inferior to its capacity") {
      #define list_length_condition \
        list->length = list->capacity - 3; \
        int original_list_length = list->length; \
        int original_list_capacity = list->capacity;

      apply(valid_element_precondition);
      apply(stack_allocated_list_condition);
      apply(list_length_condition);

      bool result = list_push(list, element);

      must("return true");
        verify(result == true);

      must("increase the list length by 1");
        verify(list->length == original_list_length + 1);

      must("copy the element at the position equal to the list length");
        verify(*(list->data + original_list_length) == element);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();

      #undef list_length_condition
    }

    when("the list length is equal to its capacity") {
      #define list_length_condition \
        list->length = list->capacity; \
        int original_list_length = list->length; \
        int original_list_capacity = list->capacity;

      apply(valid_element_precondition);
      apply(stack_allocated_list_condition);
      apply(list_length_condition);

      bool result = list_push(list, element);

      must("return false");
        verify(result == false);

      must("not copy the element on the list");
        verify(*(list->data + original_list_length - 1) == 0);

      must("leave the list length and capacity unchanged");
        verify(list->length == original_list_length);
        verify(list->capacity == original_list_capacity);


      success();

      #undef list_length_condition
    }

    #undef stack_allocated_list_condition
  }

  when("the list is heap allocated") {
    #define heap_allocated_list_condition \
      list = list_alloc(int, 16, spec_allocator);

    when("the list length is inferior to its capacity") {
      #define list_length_condition \
        list->length = list->capacity - 3; \
        int original_list_length = list->length; \
        int original_list_capacity = list->capacity;

      apply(valid_element_precondition);
      apply(heap_allocated_list_condition);
      apply(list_length_condition);

      bool result = list_push(list, element);

      must("return true");
        verify(result == true);

      must("increase the list length by 1");
        verify(list->length == original_list_length + 1);

      must("copy the element at the position equal to the list length");
        verify(*(list->data + original_list_length) == element);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();

      #undef list_length_condition
    }

    when("the list length is equal to its capacity") {
      #define list_length_condition \
        list->length = list->capacity; \
        int original_list_length = list->length; \
        int original_list_capacity = list->capacity; \
        int* original_list_data = list->data;

      apply(valid_element_precondition);
      apply(heap_allocated_list_condition);
      apply(list_length_condition);

      bool result = list_push(list, element);

      must("return true");
        verify(result == true);

      must("increase the list length by 1");
        verify(list->length == original_list_length + 1);

      must("copy the element at the position equal to the list length");
        verify(*(list->data + original_list_length) == element);

      must("double the list capacity");
        verify(list->capacity == 2*original_list_capacity);

      must("reallocate the list with the doubled capacity");
        verify(list->data != original_list_data);

      success();

      #undef list_length_condition
    }

    #undef heap_allocated_list_condition
  }

  #undef valid_type_precondition
  #undef valid_elements_precondition
}
