#include "decline/structs.h"
#include "decline/functions.h"

/**
 * Declines a map type on the provided *kt* and *vt* -- which are the key type and the
 * value type, respectively. */
#define decline_map(kt, vt)                                                         _L_ \
  decline_map_structs(kt, vt);                                                      _L_ \
  decline_map_functions(kt, vt);

/**
 * Newline replacer to beautify declination macros.
 * See `bin/compile` for more info. */
#ifndef _L_
#define _L_
#endif
