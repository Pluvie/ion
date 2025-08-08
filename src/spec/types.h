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

#define set_of char*
#include "ion/types/set.h"

#define set_of struct squadmate
#include "ion/types/set.h"

#define map_of char*, int
#include "ion/types/map.h"

#define map_of string, int
#include "ion/types/map.h"

#define map_of char*, struct squadmate
#include "ion/types/map.h"

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
    set<char*> : set<char*>_ ## f,                        \
    set<struct squadmate> : set<struct squadmate>_ ## f,  \
    _set_function(v, f, __VA_ARGS__)                      \
  )

#undef map_function
#define map_function(s, f, ...)                                           \
  _Generic(*(s),                                                          \
    map<char*, int> : map<char*, int>_ ## f,                              \
    map<string, int> : map<string, int>_ ## f,                            \
    map<char*, struct squadmate> : map<char*, struct squadmate>_ ## f,    \
    map<string, struct squadmate> : map<string, struct squadmate>_ ## f,  \
    _map_function(v, f, __VA_ARGS__)                                      \
  )

/**
 * Let's now create the definitive struct to handle all possible reflection scenarios. */
struct rfx_blueprint {
  int v_int;
  dec v_dec;
  bool v_bool;
  enum classes v_enum;
  string v_string;
  struct {
    int v_int;
  } v_struct;
  int v_array[2];
  int* v_pointer;
  struct rfx_blueprint* v_self;
  list<string> v_list;
  set<string> v_set;
  map<string, int> v_map;
};

#define b struct rfx_blueprint
struct reflection rfx_blueprint = {
  type(STRUCT, b), fields({
    { field(v_int, INT, b) },
    { field(v_dec, DEC, b) },
    { field(v_bool, BOOL, b) },
    { field(v_enum, ENUM, b) },
    { field(v_string, STRING, b) },
    { field(v_struct, STRUCT, b), fields({ { field(v_int, INT, b, v_struct) } }) },
    { field(v_array, ARRAY, b), of({ type(INT) }) },
    { field(v_pointer, POINTER, b), of({ type(INT) }) },
    { field(v_self, SELF, b) },
    { field(v_list, LIST, b), of({ type(STRING) }), container(list<string>_) },
    { field(v_set, SET, b), of({ type(STRING) }), container(set<string>_) },
    { field(v_map, MAP, b), of({ type(STRING), of({ type(INT) }) }), container(map<string, int>_) },
  })
};
#undef b
