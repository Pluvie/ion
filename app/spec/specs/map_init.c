#include "map_init.h"

spec( map_init ) {
  precondition("a greater than zero capacity")
    #define valid_capacity 8

  must("create an empty stack allocated map of the given capacity");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    map<char*, int> squad = map_init(char*, int, valid_capacity);

    verify((void*) squad.keys.data >= stack_begin);
    verify((void*) squad.keys.data <= stack_end);
    verify((void*) squad.values >= stack_begin);
    verify((void*) squad.values <= stack_end);
    verify(squad.keys.allocator == NULL);
    verify(squad.keys.capacity == valid_capacity);
    verify(squad.keys.length == 0);
    verify(squad.length == 0);

  success();
}
