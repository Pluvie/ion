#include "list_at.h"

spec( list_at ) {
  argument(list<int>* list);
  argument(unsigned int position);

  precondition("a position");
    #define preconditions \
      position = 3;

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
      verify(failure.occurred == false);

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
      verify(failure.occurred == true);
      verify(streq(failure.message, "3: overbound list position"));

    must("return nullptr");
      verify(result == nullptr);

    success();
  } end();
}
