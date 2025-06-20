test( list_pop, decrease_length ) {

  given("a list");
    list<int>* list = list_alloc(int, 16, test_allocator);
    list_push(list, 7);
    list_push(list, 8);
    list_push(list, 9);
    verify(list->length == 3);


  calling("list_pop()");
    int* element = list_pop(list);


  must("decrease the list length");
    verify(*element == 9);
    verify(list->length == 2);


  success();
}
