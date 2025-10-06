/*
  Lists.
*/

#define list_of int
#include <ion/containers/list.h>

#define list_of struct squadmate
#include <ion/containers/list.h>

#define list_function(type, func, ...)                    \
  _Generic(type,                                          \
    int :               list<int>_ ## func,               \
    struct squadmate :  list<struct squadmate>_ ## func   \
  )

/*
  Sets.
*/

#define set_of int
#include <ion/containers/set.h>

#define set_of char*
#include <ion/containers/set.h>

#define set_of struct squadmate
#include <ion/containers/set.h>

#define set_function(type, func, ...)                    \
  _Generic(type,                                         \
    int :               set<int>_ ## func,               \
    char* :             set<char*>_ ## func,             \
    struct squadmate :  set<struct squadmate>_ ## func   \
  )
