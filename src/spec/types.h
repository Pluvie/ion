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
#include "../ion/types/list.h"
