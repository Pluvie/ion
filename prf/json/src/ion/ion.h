struct coordinate {
  dec x;
  dec y;
  dec z;
};


#define list_of struct coordinate
#include <ion/containers/list.h>

#define list_function(t, f, ...)                              \
  _Generic(t,                                                 \
    list<struct coordinate> : list<struct coordinate>_ ## f,  \
  )

#define list_of struct coordinate
#include <ion/containers/list.c>


struct coordinates_data {
  list<struct coordinate> coordinates;
};

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
