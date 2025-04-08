#include "macros/map_each.h"
#include "macros/map_each_key.h"
#include "macros/map_each_value.h"
#include "macros/map_entry_is_empty.h"
#include "macros/map_entry_key.h"
#include "macros/map_entry_occupy.h"
#include "macros/map_entry_value.h"
#include "macros/map_load_limit.h"

#define map_key_at(map, index) \
  (map)->keys + (index * (map)->key_typesize)

#define map_value_at(map, index) \
  (map)->values + (index * (map)->value_typesize)

#undef map_entry_is_empty
#define map_entry_is_empty(map, index) \
  *((map)->hashes + index) == 0

#undef map_entry_occupy
#define map_entry_occupy(map, index, hash) \
  *((map)->hashes + index) = hash
