#include "list_init.h"

spec( list_init ) {

  precondition("a greater than zero capacity")
    #define valid_capacity 8

  must("create an empty stack allocated list of the given capacity");
    void* stack_begin = &(int) { 0 };
    void *stack_end = __builtin_frame_address(0);

    list<int> list = list_init(int, valid_capacity);

    verify((void*) list.data >= stack_begin);
    verify((void*) list.data <= stack_end);
    verify(list.allocator == nullptr);
    verify(list.capacity == valid_capacity);
    verify(list.length == 0);

  success();
}
