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
  unsigned int health;
  unsigned int shields;
};

#define list_of struct squadmate
#include <ion/containers/list.h>

#define list_of int
#include <ion/containers/list.h>

#define list_function(type, func, ...)                    \
  _Generic(type,                                          \
    int :               list<int>_ ## func,               \
    struct squadmate :  list<struct squadmate>_ ## func   \
  )
