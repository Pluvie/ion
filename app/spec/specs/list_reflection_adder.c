#include "list_reflection_adder.h"

spec( list_reflection_adder ) {
  argument(void* generic_list);
  argument(void* generic_element);

  precondition("a valid list");
    list<int> list = list_alloc(int, 8, spec_allocator);
    list_push(&list, 3);
    list_push(&list, 4);
    generic_list = &list;

  precondition("a valid element")
    int element = 5; generic_element = &element;

  must("behave exactly like list_push");
    list<int> list_with_push = list_alloc(int, 8, spec_allocator);
    list_push(&list_with_push, 3);
    list_push(&list_with_push, 4);

    void* result = list<int>_reflection_adder(generic_list, generic_element);
    unsigned int list_result = result - (void*) list.data;
    unsigned int list_with_push_result = list_push(&list_with_push, element);

    verify(list_result == list_with_push_result);
    verify(list.length == list_with_push.length);
    verify(list.capacity == list_with_push.capacity);
    verify(list.allocator == list_with_push.allocator);

  success();
}
