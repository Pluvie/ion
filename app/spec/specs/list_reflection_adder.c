#include "list_reflection_adder.h"

spec( list_reflection_adder ) {
  argument(void* list);
  argument(void* element);

  precondition("a valid list");
    list<int> valid_list = list_alloc(int, 8, spec_allocator);
    list_push(&valid_list, 3);
    list_push(&valid_list, 4);
    list = &valid_list;

  precondition("a valid element")
    int _element = 5; element = &_element;

  must("behave exactly like list_push");
    list<int> other_list = list_alloc(int, 8, spec_allocator);
    list_push(&other_list, 3);
    list_push(&other_list, 4);

    unsigned int result = list<int>_reflection_adder(list, element);
    unsigned int other_list_result = list_push(&other_list, *(int*) element);

    verify(result == other_list_result);
    verify(valid_list.length == other_list.length);
    verify(valid_list.capacity == other_list.capacity);
    verify(valid_list.allocator == other_list.allocator);

  success();
}
