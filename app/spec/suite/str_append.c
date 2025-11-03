#include "str_append.h"

spec( str_append ) {
  argument(str* source);
  argument(str target);
  returns(uint result);

  precondition("a valid source string");
  precondition("a valid target string");
    #define preconditions \
      str target_literal = str("HEY"); \
      target = target_literal; \
      source = allocator_push(spec_allocator, sizeof(*source)); \
      source->length = 32; \
      source->chars = allocator_push(spec_allocator, source->length); \
      memory_set(source->chars, 0, source->length);

  when("the source string has 0 length") {
    char* original_source_begin;
    apply(preconditions);
    source->length = 0;
    original_source_begin = source->chars;

    result = str_append(source, target);

    must("return 0");
      verify(result == 0);

    must("not append anything");
      verify(source->chars == original_source_begin);

    success();
  } end();

  when("the source string length is lesser than the target length") {
    char* original_source_begin;
    uint appendable_amount;
    apply(preconditions);
    source->length = target.length - 1;
    original_source_begin = source->chars;
    appendable_amount = source->length;

    result = str_append(source, target);

    must("return the appendable amount");
      verify(result == appendable_amount);

    must("append the corresponding amount of characters");
      verify(source->chars == original_source_begin + appendable_amount);
      verify(source->chars[-2] == 'H');
      verify(source->chars[-1] == 'E');

    must("reduce the source length to 0");
      verify(source->length == 0);

    success();
  } end();

  when("the source string length is not lesser than the target length") {
    char* original_source_begin;
    uint appendable_amount;
    apply(preconditions);
    source->length = target.length + 1;
    original_source_begin = source->chars;
    appendable_amount = target.length;

    result = str_append(source, target);

    must("return the appendable amount");
      verify(result == appendable_amount);

    must("append the corresponding amount of characters");
      verify(source->chars == original_source_begin + appendable_amount);
      verify(source->chars[-3] == 'H');
      verify(source->chars[-2] == 'E');
      verify(source->chars[-1] == 'Y');

    must("reduce the source length to 1");
      verify(source->length == 1);

    success();
  } end();
}
