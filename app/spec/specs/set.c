#include "set.h"

spec( set ) {
  precondition("a valid list of elements for the set")
    #define valid_elements { \
      "Jane Shepard", \
      "Garrus Vakarian", \
      "Liara T'Soni", \
    }

  must("create a frozen stack allocated set of the given elements");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    set<char*> squad = set(char*, valid_elements);

    verify((void*) squad.data >= stack_begin);
    verify((void*) squad.data <= stack_end);
    verify(squad.allocator == nullptr);
    verify(squad.capacity == 3);
    verify(squad.length == 3);

  success();
}
