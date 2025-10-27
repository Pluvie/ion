#include "../spec.h"

static struct {
  cstr fatal;
} sim;

static struct cstr_int_map unallocated_map = { 0 };
cstr unallocated_map_keys[8] = { 0 };
int unallocated_map_values[8] = { 0 };
uint unallocated_map_hashes[8] = { 0 };

#undef  fatal
#define fatal(msg)  sim.fatal = msg
