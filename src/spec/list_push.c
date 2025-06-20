spec( list_push ) {

  argument(list<int>* list);
  argument(int element);

  precondition("a valid list");
    #define valid_list_precondition \
      list = list_alloc(int, 16, spec_allocator);

  precondition("a valid element")
    #define valid_element_precondition \
      element = 7;

  when("the list length is inferior to its capacity - 1") {
    #define list_length_condition \
      list->length = 2; \
      verify(list->length < list->capacity - 1);

    apply(valid_list_precondition);
    apply(valid_element_precondition);
    apply(list_length_condition);

    bool result = list_push(list, element);

    must("return true");
      verify(result == true);

    must("increase the list length by 1");
      verify(list->length == 3);

    must("copy the element at the position equal to the list length");
      verify(*(list->data + 2) == element);

    must("leave the list capacity unchanged");
      verify(list->capacity == 16);

    success();

    #undef list_length_condition
  }

  when("the list length is equal to its capacity - 1") {
    #define list_length_condition \
      list->length = 15; \
      verify(list->length == list->capacity - 1);
      int* original_list_data = list->data;

    apply(valid_list_precondition);
    apply(valid_element_precondition);
    apply(list_length_condition);

    bool result = list_push(list, element);

    must("return true");
      verify(result == true);

    must("increase the list length by 1");
      verify(list->length == 16);

    must("copy the element at the position equal to the list length");
      verify(*(list->data + 15) == element);

    must("double the list capacity");
      verify(list->capacity == 16);

    must("reallocate the list with the doubled capacity");
      verify(list->data != original_list_data);

    success();

    #undef list_length_condition
  }

  when("the list does not have an allocator") {
    #define list_allocator_condition \
      list->allocator = NULL; \
      list->length = 5;

    apply(valid_list_precondition);
    apply(valid_element_precondition);
    apply(list_allocator_condition);

    bool result = list_push(list, element);

    must("return false");
      verify(result == true);

    must("not copy the element on the list");
      verify(*(list->data + 5) == 0);

    must("leave the list length and capacity unchanged");
      verify(list->length == 5);
      verify(list->capacity == 16);

    success();

    #undef list_allocator_condition
  }

  #undef valid_type_precondition
  #undef valid_elements_precondition
}
