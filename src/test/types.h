/**
 * In this test we're going to define some more complex types, as it usually happens in
 * a proper application.
 *
 * When defining a custom type, it is mandatory to provide the `hash` and `cmp`
 * functions if you want to utilize data structures on that type. */

enum classes {
  SOLDIER,
  VANGUARD,
  INFILTRATOR,
  ENGINEER,
  SENTINEL,
  ADEPT,
};

struct squadmate {
  string name;
  enum classes class;
  int health;
  int shields;
};

int hash<struct squadmate> (
    struct squadmate c
)
{
  return hash<string>(c.name);
}

int cmp<struct squadmate> (
    struct squadmate c1,
    struct squadmate c2
)
{
  return cmp<string>(c1.name, c2.name);
}

#undef cmp
#define cmp(v1, v2)                             \
  _Generic(v1,                                  \
    struct squadmate : cmp<struct squadmate>,   \
    _cmp(v1, v2)                                \
  )(v1, v2)

#undef hash
#define hash(v)                                 \
  _Generic(v,                                   \
    struct squadmate : hash<struct squadmate>,  \
    _hash(v)                                    \
  )(v)

/**
 * Now let's add some more containers. */

#define list_of list<int>
#include "ion/types/list.h"

#define list_of struct squadmate
#include "ion/types/list.h"

#define set_of struct squadmate
#include "ion/types/set.h"

#define map_of string, struct squadmate
#include "ion/types/map.h"

#undef list_function
#define list_function(s, f, ...)                            \
  _Generic(*(s),                                            \
    list<struct squadmate> : list<struct squadmate>_ ## f,  \
    _list_function(v, f, __VA_ARGS__)                       \
  )

#undef set_function
#define set_function(s, f, ...)                           \
  _Generic(*(s),                                          \
    set<struct squadmate> : set<struct squadmate>_ ## f,  \
    _set_function(v, f, __VA_ARGS__)                      \
  )

#undef map_function
#define map_function(s, f, ...)                                           \
  _Generic(*(s),                                                          \
    map<string, struct squadmate> : map<string, struct squadmate>_ ## f,  \
    _map_function(v, f, __VA_ARGS__)                                      \
  )
