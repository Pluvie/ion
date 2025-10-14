#include "../spec.h"
#include "../containers.h"

static struct {
  unsigned int hash_result;
  unsigned int probe_count;
  unsigned int probe_indexes[16];
} sim;

/*
  Redefines the `set_pos_is_free` macro to keep track of the probe index.
*/
#undef  set_pos_is_free
#define set_pos_is_free(s, p) ( \
  ((s)->hashes[p] == (unsigned int) 0) ? true : \
  (sim.probe_indexes[sim.probe_count++] = p, false))

/*
  Occupies a position in the set for testing purposes.
*/
#define set_occupy(s, p) \
  set_pos_occupy(s, p, 0); set->data[p] = "placeholder"

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define T       char*
#define _pos    _pos_specced
#define set_cmp_function(v, u) cstr_equal(v, u)
#define set_hash_function(v) sim.hash_result
#include <ion/containers/set/functions/set_pos.c>

/*
  Redefines the `set_pos` macro to point to the specced function.
*/
#undef  set_pos
#define set_pos(s, e) \
  set<T>_pos_specced(s, e)
