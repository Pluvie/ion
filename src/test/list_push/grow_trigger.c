test( list_push, grow_trigger ) {

  given("a list");
    list<int>* list = list_alloc(int, 16, test_allocator);
    void* original_list_data = list->data;
    int original_list_capacity = list->capacity;


  when("the list has some elements in it, under the capacity");
    for (int index = 0; index < original_list_capacity; index++)
      list_push(list, index);


  when("adding a new element and surpassing the load limit");
    int element = 999;


  calling("list_push()");
    list_push(list, element);


  must("trigger the list grow");
    verify(list->data != original_list_data);
    verify(list->capacity == original_list_capacity * 2);
    verify(list->length == original_list_capacity + 1);


  success();
}
