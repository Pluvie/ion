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
  list<int> numbers;
  dec matrix[3][3];
} example;

static struct reflection squadmate_reflection =
  reflect(struct squadmate, STRUCT, fields(
    field(struct squadmate, STR, name),
    field(struct squadmate, ENUM, class),
    field(struct squadmate, INT, health),
    field(struct squadmate, INT, shields),
  )
);

static struct reflection example_reflection =
  reflect(struct example, STRUCT, fields(
    field(struct example, INT, integer),
    field(struct example, DEC, decimal),
    field(struct example, STR, string),
    field(struct example, BOOL, boolean),
    field(struct example, SET, strings,
      of(reflect(str, STR)),
      container(set, str)
    ),
    field(struct example, MAP, squad,
      of(reflect(str, STR, of(squadmate_reflection))),
      container(map, str, struct squadmate)
    ),
    field(struct example, LIST, numbers,
      of(reflect(int, INT)),
      container(list, int)
    ),
    field(struct example, ARRAY, matrix, of(reflect(dec, DEC))),
  )
);



struct coordinate {
  dec x;
  dec y;
  dec z;
};

#define list_of struct coordinate
#include <ion/containers/list.h>

#define list_of struct coordinate
#include <ion/containers/list.c>

static struct coordinates_data {
  list<struct coordinate> coordinates;
} coordinates_data;

struct reflection coordinate_reflection =
  reflect(struct coordinate, STRUCT, fields(
    field(struct coordinate, DEC, x),
    field(struct coordinate, DEC, y),
    field(struct coordinate, DEC, z),
  )
);

struct reflection coordinates_data_reflection =
  reflect(struct coordinates_data, STRUCT, fields(
    field(struct coordinates_data, LIST, coordinates,
      of(coordinate_reflection), container(list, struct coordinate)),
  )
);
