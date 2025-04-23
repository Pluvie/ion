/**
 * Declines the set on the `string` element type. */
#define   set_declination string
#define   set_use_comparer
static inline bool set_comparer(string) (
    string* e1,
    string* e2
)
{
  return streq(*e1, *e2);
}
#define   set_use_hasher
static inline u64 set_hasher(string) (
    string* element
)
{
  u64 hash = 5381;

  for (u64 i = 0; i < element->length; i++)
    hash = ((hash << 5) + hash) + ((u8*) element)[i];

  return hash;
}
#include  "ion/modules/set/declination.h"
