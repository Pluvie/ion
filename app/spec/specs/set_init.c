#include "set_init.h"

spec( set_init ) {
  precondition("a greater than zero capacity")
    #define valid_capacity 8

  must("create an empty stack allocated set of the given capacity");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    set<struct squadmate> squad = set_init(struct squadmate, valid_capacity);

    verify((void*) squad.data >= stack_begin);
    verify((void*) squad.data <= stack_end);
    verify(squad.allocator == nullptr);
    verify(squad.capacity == valid_capacity);
    verify(squad.length == 0);

  success();
}
