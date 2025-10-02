#include "list.h"

spec( list ) {

  precondition("a valid list of elements of that type")
    #define valid_elements { \
        { string("Jane Shepard"),     SOLDIER,      800,  400 }, \
        { string("Garrus Vakarian"),  INFILTRATOR,  600,  600 }, \
        { string("Liara T'Soni"),     ADEPT,        200,  800 }, \
      }

  must("create a frozen stack allocated list of the given elements");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    list<struct squadmate> squad = list(struct squadmate, valid_elements);
    list<struct squadmate> squad2 = list_init(struct squadmate, 8);
    verify(squad2.length == 0);
    verify(squad2.capacity == 8);

    verify((void*) squad.data >= stack_begin);
    verify((void*) squad.data <= stack_end);
    verify(squad.allocator == nullptr);
    verify(squad.capacity == 3);
    verify(squad.length == 3);

  success();
}
