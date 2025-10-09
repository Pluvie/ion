/*
  Lists.
*/

#define list_of int
#include <ion/containers/list.h>

#define list_of struct squadmate
#include <ion/containers/list.h>

#define list_function(type, func, ...)                          \
  _Generic(type,                                                \
    list<int>               : list<int>_ ## func,               \
    list<struct squadmate>  : list<struct squadmate>_ ## func   \
  )

/*
  Sets.
*/

#define set_of int
#include <ion/containers/set.h>

#define set_of char*
#include <ion/containers/set.h>

#define set_of str
#include <ion/containers/set.h>

#define set_of struct squadmate
#include <ion/containers/set.h>

#define set_function(type, func, ...)                         \
  _Generic(type,                                              \
    set<int>              : set<int>_ ## func,                \
    set<char*>            : set<char*>_ ## func,              \
    set<str>              : set<str>_ ## func,             \
    set<struct squadmate> : set<struct squadmate>_ ## func    \
  )

/*
  Maps.
*/

#define map_of char*, int
#include <ion/containers/map.h>

#define map_of char*, struct squadmate
#include <ion/containers/map.h>

#define map_of str, struct squadmate
#include <ion/containers/map.h>

#define map_function(type, func, ...)                                       \
  _Generic(type,                                                            \
    map<char*, int>               : map<char*, int>_ ## func,               \
    map<char*, struct squadmate>  : map<char*, struct squadmate>_ ## func,  \
    map<str, struct squadmate>    : map<str, struct squadmate>_ ## func  \
  )
