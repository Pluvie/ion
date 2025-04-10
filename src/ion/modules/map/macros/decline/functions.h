#include "functions/decline_map_del.h"
#include "functions/decline_map_get.h"
#include "functions/decline_map_init.h"
#include "functions/decline_map_rehash.h"
#include "functions/decline_map_set.h"

#define decline_map_functions(kt, vt)                                               _L_ \
                                                                                    _L_ \
static inline u64 map_hasher(kt, vt) (                                              _L_ \
    kt* key                                                                         _L_ \
);                                                                                  _L_ \
                                                                                    _L_ \
static inline bool map_comparer(kt, vt) (                                           _L_ \
    kt* k1,                                                                         _L_ \
    kt* k2                                                                          _L_ \
);                                                                                  _L_ \
                                                                                    _L_ \
vt* map_del(kt, vt) (                                                               _L_ \
    map(kt, vt)* m,                                                                 _L_ \
    kt* key                                                                         _L_ \
);                                                                                  _L_ \
                                                                                    _L_ \
vt* map_get(kt, vt) (                                                               _L_ \
    map(kt, vt)* m,                                                                 _L_ \
    kt* key                                                                         _L_ \
);                                                                                  _L_ \
                                                                                    _L_ \
map(kt, vt) map_init(kt, vt) (                                                      _L_ \
    u64 initial_capacity,                                                           _L_ \
    memory* allocator                                                               _L_ \
);                                                                                  _L_ \
                                                                                    _L_ \
void map_rehash(kt, vt) (                                                           _L_ \
    map(kt, vt)* m                                                                  _L_ \
);                                                                                  _L_ \
                                                                                    _L_ \
vt* map_set(kt, vt) (                                                               _L_ \
    map(kt, vt)* m,                                                                 _L_ \
    kt* key,                                                                        _L_ \
    vt* value                                                                       _L_ \
);                                                                                  _L_ \
                                                                                    _L_ \
decline_map_del(kt, vt);                                                            _L_ \
decline_map_get(kt, vt);                                                            _L_ \
decline_map_init(kt, vt);                                                           _L_ \
decline_map_rehash(kt, vt);                                                         _L_ \
decline_map_set(kt, vt);

/**
 * `map_comparer` and `map_hasher` **must** be implemented by the user, following the
 * functions definition.
 *
 * Alternatively, to use the default comparer and hasher functions, invoke the macros:
 * `decline_map_comparer_default(kt, vt)` and `decline_map_hasher_default(kt, vt)`. */
#include "functions/decline_map_comparer_default.h"
#include "functions/decline_map_hasher_default.h"
