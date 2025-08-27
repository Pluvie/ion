spec( list_push ) {

  argument(list<int>* list);
  argument(int element);

  precondition("a valid element of the list type")
    #define preconditions \
      element = 7;

  when("the list is stack allocated") {
    when("the list length is inferior to its capacity") {
      apply(preconditions);
      list<int> stack_list = list_init(int, 16);
      list = &stack_list;
      list->length = list->capacity - 3;
      int original_list_length = list->length;
      int original_list_capacity = list->capacity;
      bool result = list_push(list, element);

      must("not fail");
        verify(failure.occurred == false);

      must("return true");
        verify(result == true);

      must("increase the list length by 1");
        verify(list->length == original_list_length + 1);

      must("copy the element at the position equal to the list length");
        verify(*(list->data + original_list_length) == element);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();
    } end();

    when("the list length is equal to its capacity") {
      apply(preconditions);
      list<int> stack_list = list_init(int, 16);
      list = &stack_list;
      list->length = list->capacity;
      int original_list_length = list->length;
      int original_list_capacity = list->capacity;
      bool result = list_push(list, element);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is("push: stack allocated list is full"));

      must("return false");
        verify(result == false);

      must("not copy the element on the list");
        verify(*(list->data + original_list_length - 1) == 0);

      must("leave the list length and capacity unchanged");
        verify(list->length == original_list_length);
        verify(list->capacity == original_list_capacity);


      success();
    } end();
  } end();

  when("the list is heap allocated") {
    when("the list length is inferior to its capacity") {
      apply(preconditions);
      list = list_alloc(int, 16, spec_allocator);
      list->length = list->capacity - 3;
      int original_list_length = list->length;
      int original_list_capacity = list->capacity;
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
    } end();

    when("the list length is equal to its capacity") {
      apply(preconditions);
      list = list_alloc(int, 16, spec_allocator);
      list->length = list->capacity;
      int original_list_length = list->length;
      int original_list_capacity = list->capacity;
      void* original_list_data = list->data;
      bool result = list_push(list, element);

      must("not fail");
        verify(failure.occurred == false);

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
    } end();
  } end();

  #undef preconditions
}
