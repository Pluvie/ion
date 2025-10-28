#include "../spec.h"

static struct {
  cstr fatal;
} sim;

static struct cstr_int_map unallocated_map = { 0 };
static cstr unallocated_map_keys[8] = { 0 };
static int unallocated_map_values[8] = { 0 };
static uint unallocated_map_hashes[8] = { 0 };

static void unallocated_map_init (
    void
)
{
  memory_set(unallocated_map_keys, 0, sizeof(unallocated_map_keys));
  memory_set(unallocated_map_values, 0, sizeof(unallocated_map_values));
  memory_set(unallocated_map_hashes, 0, sizeof(unallocated_map_hashes));
  unallocated_map = cstr_int_map_init(8,
    unallocated_map_keys, unallocated_map_values, unallocated_map_hashes);
}

#define fatal(msg)  sim.fatal = msg

/* Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.

  In this case the spec-specific function copy is a bit more complex than the others.
  We have infact to recreate the precise environment where the functions `set_add`
  and `map_set` are defined. This usually happens in container definition code -- see
  `../containers.c` -- and looks like this:

  ```c
  #define container_for_key cstr
  #define container_for_value int
  #define container_name cstr_int_map
  #define container_equalizer(a, b) cstr_equal(a, b)
  #define container_hasher(e) hash_djb2_cstr(e)
  #include <ion/containers/map.c>
  ```

  The last include statement creates all the macros and types needed for the definition
  of the `set_add` and `map_set` functions. We shall then replicate its behaviour here
  in order to create a spec-specific copy of those functions. */

#define concat_function(name, func) name ## _ ## func
#define container_function(name, func) concat_function(name, func)
#define container_hasher(e) hash_djb2_cstr(e)

#define N cstr_int_map_keys
#define T cstr
#define cstr_int_map_keys_add    specced__cstr_int_map_keys_add
#include <ion/containers/set/macros.h>
#include <ion/containers/set/functions/set_add.c>

#undef  N
#define S cstr_int_map_keys
#define N cstr_int_map
#define K cstr
#define V int
#define cstr_int_map_set    specced__cstr_int_map_set
#include <ion/containers/map/functions/map_set.c>
#include <ion/containers/set/macros.h>
