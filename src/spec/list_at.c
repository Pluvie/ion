spec( list_at ) {

  argument(list<int>* list);
  argument(int position);

  precondition("a non-negative position");
    #define preconditions \
      position = 3;

  when("the list is stack allocated") {
    when("the position is inferior to the list length") {
      apply(preconditions);
      list<int> stack_list = list_init(int, 16);
      list = &stack_list;
      list_push(list, 1);
      list_push(list, 2);
      list_push(list, 3);
      list_push(list, 4);
      list_push(list, 5);
      int* result = list_at(list, position);

      must("not fail");
        verify(error.occurred == false);

      must("return the element at the specified position");
        verify(*result == 4);

      success();
    } end();

    when("the position is greater or equal than the list length") {
      apply(preconditions);
      list<int> stack_list = list_init(int, 16);
      list = &stack_list;
      list_push(list, 1);
      list_push(list, 2);
      list_push(list, 3);
      int* result = list_at(list, position);

      must("fail with a specific error");
        verify(error.occurred == true);
        verify(streq(error.message, "3: overbound list position"));

      must("return NULL");
        verify(result == NULL);

      success();
    } end();
  } end();

  when("the list is heap allocated") {
    when("the position is inferior to the list length") {
      apply(preconditions);
      list = list_alloc(int, 16, spec_allocator);
      list_push(list, 1);
      list_push(list, 2);
      list_push(list, 3);
      list_push(list, 4);
      list_push(list, 5);
      int* result = list_at(list, position);

      must("not fail");
        verify(error.occurred == false);

      must("return the element at the specified position");
        verify(*result == 4);

      success();
    } end();

    when("the position is greater or equal than the list length") {
      apply(preconditions);
      list = list_alloc(int, 16, spec_allocator);
      list_push(list, 1);
      list_push(list, 2);
      list_push(list, 3);
      int* result = list_at(list, position);

      must("fail with a specific error");
        verify(error.occurred == true);
        verify(streq(error.message, "3: overbound list position"));

      must("return NULL");
        verify(result == NULL);

      success();
    } end();
  } end();

  #undef preconditions
}
