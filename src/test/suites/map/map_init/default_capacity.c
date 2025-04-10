#define   map_declination i32, i32

#define   map_use_comparer
static inline bool map_comparer(i32, i32) (
    i32* k1,
    i32* k2
)
{
  return *k1 == *k2;
}

#define   map_use_hasher
static inline u64 map_hasher(i32, i32) (
    i32* key
)
{
  return (u64) *key;
}
#include  "../../../../ion/modules/map/declination.h"

test( map_init, default_capacity ) {

  given("a declined map");
    map(i32, i32) m;
    memory allocator = memory_init(0);


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("map_init()");
    m = map_init(i32, i32)(capacity, &allocator);


  must("initialize the map with #MAP_CAPACITY_DEFAULT capacity");
    verify(m.capacity == MAP_CAPACITY_DEFAULT);


  success();
    memory_release(&allocator);
}
