# 0 "src/spec/types.h"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "src/spec/types.h"
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


# 1 "src/spec/../ion/types/list.h" 1




# 1 "src/spec/../ion/types/list/struct.h" 1
typedef struct list<struct squadmate> {
  struct squadmate* data;
  int length;
  int capacity;
  struct allocator* allocator;
} list<struct squadmate>;
check_sizeof(32, list<struct squadmate>);
# 6 "src/spec/../ion/types/list.h" 2
# 1 "src/spec/../ion/types/list/functions.h" 1
# 7 "src/spec/../ion/types/list.h" 2
# 1 "src/spec/../ion/types/list/reflection.h" 1
# 8 "src/spec/../ion/types/list.h" 2
# 19 "src/spec/types.h" 2
