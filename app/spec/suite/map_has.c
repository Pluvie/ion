#include "map_has.h"

spec( map_has ) {
  argument(struct cstr_int_map* map);
  argument(char* key);
  returns(bool result);

  precondition("a valid map");
    #define preconditions \
      map = allocator_push(spec_allocator, sizeof(*map)); \
      *map = cstr_int_map_alloc(16, spec_allocator); \
      cstr_int_map_set(map, "a", 7); \
      cstr_int_map_set(map, "b", 8); \
      cstr_int_map_set(map, "c", 9);

  when("the key is present in the map") {
    key = "a";
    apply(preconditions);
    result = cstr_int_map_has(map, key);

    must("return true");
      verify(result == true);

    success();
  } end();

  when("the key is not present in the map") {
    key = "f";
    apply(preconditions);
    result = cstr_int_map_has(map, key);

    must("return false");
      verify(result == false);

    success();
  } end();
}
