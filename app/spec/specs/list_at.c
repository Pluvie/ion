#include "list_at.h"

spec( list_at ) {
  argument(list<int>* list);
  argument(unsigned int position);

  precondition("a position");
    #define preconditions \
      position = 3;

  when("the position is inferior to the list length") {
    apply(preconditions);
    list = allocator_push(spec_allocator, sizeof(*list));
    *list = list_alloc(int, 16, spec_allocator);
    list_push(list, 1);
    list_push(list, 2);
    list_push(list, 3);
    list_push(list, 4);
    list_push(list, 5);
    int* result = list_at(list, position);

    must("return the element at the specified position");
      verify(*result == 4);

    success();
  } end();

  when("the position is greater or equal than the list length") {
    apply(preconditions);
    list = allocator_push(spec_allocator, sizeof(*list));
    *list = list_alloc(int, 16, spec_allocator);
    list_push(list, 1);
    list_push(list, 2);
    list_push(list, 3);
    list_at(list, position);

    must("fatally fail with a specific message");
      printl(">>>> ", sim.fatal);
      verify(cstreq(sim.fatal, "3: overbound list position"));

    success();
  } end();
}
