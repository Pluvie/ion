#include "spec.h"

/* Defines the containers implementations. */
#define container_for_key cstr
#define container_for_value int
#define container_name cstr_int_map
#define container_equalizer(a, b) cstr_equal(a, b)
#define container_hasher(e) hash_djb2_cstr(e)
#include <ion/containers/map.c>
