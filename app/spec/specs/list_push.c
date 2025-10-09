#include "list_push.h"

spec( list_push ) {
  argument(list<int>* list);
  argument(int element);

  precondition("a valid element of the list type")
    #define preconditions \
      element = 7;

  when("the list is stack allocated") {
    when("the list length is inferior to its capacity") {
      apply(preconditions);
      list<int> stack_list = list_init(int, 16);
      list = &stack_list;
      list->length = list->capacity - 3;
      unsigned int original_list_length = list->length;
      unsigned int original_list_capacity = list->capacity;
      unsigned int result = list_push(list, element);

      must("return the inserted position");
        verify(result == original_list_length);

      must("increase the list length by 1");
        verify(list->length == original_list_length + 1);

      must("copy the element at the position equal to the list length");
        verify(*(list->data + original_list_length) == element);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();
    } end();

    when("the list length is equal to its capacity") {
      apply(preconditions);
      list<int> stack_list = list_init(int, 16);
      list = &stack_list;
      list->length = list->capacity;
      list_push(list, element);

      must("fatally fail with a specific message");
        verify(cstreq(sim.fatal, "push: stack allocated list is full"));

      success();
    } end();
  } end();

  when("the list is heap allocated") {
    when("the list length is inferior to its capacity") {
      apply(preconditions);
      list = allocator_push(spec_allocator, sizeof(*list));
      *list = list_alloc(int, 16, spec_allocator);
      list->length = list->capacity - 3;
      unsigned int original_list_length = list->length;
      unsigned int original_list_capacity = list->capacity;
      unsigned int result = list_push(list, element);

      must("return the inserted position");
        verify(result == original_list_length);

      must("increase the list length by 1");
        verify(list->length == original_list_length + 1);

      must("copy the element at the position equal to the list length");
        verify(*(list->data + original_list_length) == element);

      must("leave the list capacity unchanged");
        verify(list->capacity == original_list_capacity);

      success();

      #undef list_length_condition
    } end();

    when("the list length is equal to its capacity") {
      apply(preconditions);
      list = allocator_push(spec_allocator, sizeof(*list));
      *list = list_alloc(int, 16, spec_allocator);
      list->length = list->capacity;
      unsigned int original_list_length = list->length;
      unsigned int original_list_capacity = list->capacity;
      void* original_list_data = list->data;
      unsigned int result = list_push(list, element);

      must("return the inserted position");
        verify(result == original_list_length);

      must("increase the list length by 1");
        verify(list->length == original_list_length + 1);

      must("copy the element at the position equal to the list length");
        verify(*(list->data + original_list_length) == element);

      must("double the list capacity");
        verify(list->capacity == 2*original_list_capacity);

      must("reallocate the list with the doubled capacity");
        verify(list->data != original_list_data);

      success();
    } end();
  } end();

  #undef preconditions
}
