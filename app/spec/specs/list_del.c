#include "list_del.h"

spec( list_del ) {
  argument(list<int>* list);
  argument(int element);

  when("the element is in the list") {
    element = 6;
    list = allocator_push(spec_allocator, sizeof(*list));
    *list = list_alloc(int, 16, spec_allocator);
    list_push(list, 5);
    list_push(list, 6);
    list_push(list, 7);
    list_push(list, 8);
    list_push(list, 9);
    unsigned int original_list_length = list->length;
    unsigned int original_list_capacity = list->capacity;
    unsigned int result = list_del(list, element);

    must("decrease the list length by 1");
      verify(list->length == original_list_length - 1);

    must("compact the list");
      verify(list->data[0] == 5);
      verify(list->data[1] == 7);
      verify(list->data[2] == 8);
      verify(list->data[3] == 9);

    must("return the position of the deleted element");
      verify(result == 1);

    must("leave the list capacity unchanged");
      verify(list->capacity == original_list_capacity);

    success();
  } end();

  when("the element is not in the list") {
    element = 11;
    list = allocator_push(spec_allocator, sizeof(*list));
    *list = list_alloc(int, 16, spec_allocator);
    list_push(list, 5);
    list_push(list, 6);
    list_push(list, 7);
    list_push(list, 8);
    list_push(list, 9);
    unsigned int original_list_length = list->length;
    unsigned int original_list_capacity = list->capacity;
    unsigned int result = list_del(list, element);

    must("return -1");
      verify(result == (unsigned int) -1);

    must("leave the list length unchanged");
      verify(list->length == original_list_length);

    must("leave the list capacity unchanged");
      verify(list->capacity == original_list_capacity);

    success();
  } end();
}
