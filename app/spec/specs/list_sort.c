#include "list_sort.h"

spec( list_sort ) {
  argument(list<int>* list);
  argument(int (*cmp_function)(int*, int*));

  precondition("a valid list");
  precondition("a valid comparison function");
    #define preconditions \
      list<int> stack_list = list(int, { 7, 11, 3, 19, 27, 1 }); \
      list = &stack_list; \
      cmp_function = int_cmp;

  apply(preconditions);
  unsigned int original_list_length = list->length;
  unsigned int original_list_capacity = list->capacity;

  list_sort(list, cmp_function);

  must("sort the elements of the list according to the comparison function");
    verify(*list_at(list, 0) == 1);
    verify(*list_at(list, 1) == 3);
    verify(*list_at(list, 2) == 7);
    verify(*list_at(list, 3) == 11);
    verify(*list_at(list, 4) == 19);
    verify(*list_at(list, 5) == 27);

  must("leave the list capacity unchanged");
    verify(list->capacity == original_list_capacity);

  must("leave the list length unchanged");
    verify(list->length == original_list_length);

  success();
}
