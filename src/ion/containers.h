/**
 * Define some ready to use containers, some of which are used in the ⚡️ION⚡️ code
 * itself. */

/**
 * Lists. */

#define list_of int
#include "ion/types/list.h"

#define list_of string
#include "ion/types/list.h"

#define list_of struct reflection
#include "ion/types/list.h"

#define _list_function(v, f, ...)                         \
  list<int> : list<int>_ ## f,                            \
  list<string> : list<string>_ ## f,                      \
  list<struct reflection> : list<struct reflection>_ ## f \

#define list_function(v, f, ...)              \
  _Generic(*(v),                              \
    _list_function(v, f, __VA_ARGS__)         \
  )

/**
 * Sets. */

#define set_of int
#include "ion/types/set.h"

#define set_of string
#include "ion/types/set.h"

#define _set_function(v, f, ...)    \
  set<int> : set<int>_ ## f,        \
  set<string> : set<string>_ ## f   \

#define set_function(v, f, ...)       \
  _Generic(*(v),                      \
    _set_function(v, f, __VA_ARGS__)  \
  )

/**
 * Maps. */

#define map_of int, int
#include "ion/types/map.h"

#define map_of string, string
#include "ion/types/map.h"

#define _map_function(v, f, ...)                    \
  map<int, int> : map<int, int>_ ## f,              \
  map<string, string> : map<string, string>_ ## f   \

#define map_function(v, f, ...)       \
  _Generic(*(v),                      \
    _map_function(v, f, __VA_ARGS__)  \
  )
