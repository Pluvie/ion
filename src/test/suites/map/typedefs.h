/**
 * Declines the map on the `i32`, `i32` key/value type. Used for some tests. */
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
#include  "ion/modules/map/declination.h"

/**
 * Declines the map on the `string`, `string` key/value type. Used for some tests. */
#define   map_declination string, string
#define   map_use_comparer
#define   map_use_hasher

static inline bool map_comparer(string, string) (
    string* k1,
    string* k2
)
{
  return streq(*k1, *k2);
}

static inline u64 map_hasher(string, string) (
    string* key
)
{
  u64 hash = 5381;

  for (u64 i = 0; i < key->length; i++)
    hash = ((hash << 5) + hash) + ((u8*) key)[i];

  return hash;
}
#include  "ion/modules/map/declination.h"

/**
 * Declines the map on the `string`, `User` key/value type. Used for some tests. */
#define map_declination string, User
#define map_use_comparer
#define map_use_hasher

static inline bool map_comparer(string, User) (
    string* k1,
    string* k2
)
{
  return streq(*k1, *k2);
}

static inline u64 map_hasher(string, User) (
    string* key
)
{
  u64 hash = 5381;

  for (u64 i = 0; i < key->length; i++)
    hash = ((hash << 5) + hash) + ((u8*) key)[i];

  return hash;
}
#include "ion/modules/map/declination.h"
