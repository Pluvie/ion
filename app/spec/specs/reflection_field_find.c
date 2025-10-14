#include "reflection_field_find.h"

spec( reflection_field_find ) {
  argument(struct reflection* reflection);
  argument(str* field_name);

  precondition("a valid reflection with initialized fields");
  precondition("a valid string as field name");
    #define preconditions \
      reflection = &(struct reflection) { \
        fields( \
          { .type = INT, .name = string("aaa") }, \
          { .type = DEC, .name = string("bbb") }, \
          { .type = STR, .name = string("ccc") }, \
        ), \
      }; \
      field_name = &source;

  when("the field name is not present in the reflection fields") {
    str source = string("ddd");
    apply(preconditions);
    struct reflection* result = reflection_field_find(reflection, field_name);

    must("return nullptr");
      verify(result == nullptr);

    success();
  } end();

  when("the field name is present in the reflection fields") {
    str source = string("bbb");
    apply(preconditions);
    struct reflection* result = reflection_field_find(reflection, field_name);

    must("return a pointer to the field");
      verify(result != nullptr);
      verify(str_equal(result->name, *field_name));

    success();
  } end();
}
