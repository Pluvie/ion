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

#define list_function(type, func, ...)                  \
  _Generic(type,                                        \
    struct squadmate : list<struct squadmate>_ ## func  \
  )
