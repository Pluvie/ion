#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

static struct example {
  int integer;
  dec decimal;
  str string;
  bool boolean;
  set<str> strings;
  map<str, struct squadmate> squad;
} example;

static struct reflection squadmate_reflection =
  reflect(struct squadmate, STRUCT, fields(
    { field(struct squadmate, STR, name) },
    { field(struct squadmate, ENUM, class) },
    { field(struct squadmate, INT, health) },
    { field(struct squadmate, INT, shields) },
  )
);

static struct reflection example_reflection =
  reflect(struct example, STRUCT, fields(
    { field(struct example, INT, integer) },
    { field(struct example, DEC, decimal) },
    { field(struct example, STR, string) },
    { field(struct example, BOOL, boolean) },
    { field(struct example, SET, strings), of(reflect(str, STR)) },
    { field(struct example, MAP, squad), of(
        reflect(str, STR, of(squadmate_reflection))
    )},
  )
);
