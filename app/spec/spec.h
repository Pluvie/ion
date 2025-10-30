#include <ion.h>
#include <ion/spec.h>

/* Some types defined in the specs to give examples on user defined types. */
enum classes {
  SOLDIER,
  VANGUARD,
  INFILTRATOR,
  ENGINEER,
  SENTINEL,
  ADEPT
};

struct squadmate {
  str name;
  enum classes class;
  uint health;
  uint shields;
};

/* Let's now declare some containers. */
#define container_for_key cstr
#define container_for_value int
#define container_name cstr_int_map
#include <ion/containers/map.h>

#define container_for_key cstr
#define container_for_value struct squadmate
#define container_name squad_map
#include <ion/containers/map.h>

#if standard(>= C23)
#define map_function(type, func)                  \
  _Generic(type,                                  \
    struct cstr_int_map : cstr_int_map_ ## func,  \
    struct squad_map    : squad_map_ ## func      \
  )
#endif
