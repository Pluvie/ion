test( list_pop, zero_length ) {

  given("a list");
    list<int>* list = list_alloc(int, 16, test_allocator);
    verify(list->length == 0);


  calling("list_pop()");
    int* element = list_pop(list);


  must("return NULL");
    verify(element == NULL);
    verify(list->length == 0);


  success();
}
