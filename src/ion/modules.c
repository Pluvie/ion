/* ⚡️ION⚡️ base module: required for every other module. */
#include "modules/core.c"

/* ⚡️ION⚡️ Modules requiring the CORE module only. */
#include "modules/array.c"
#include "modules/io.c"
#include "modules/map.c"
#include "modules/range.c"
#include "modules/string.c"
#include "modules/time.c"
#include "modules/vector.c"

/* ⚡️ION⚡️ Modules requiring the RANGE and VECTOR module. */
#include "modules/tensor.c"

/* ⚡️ION⚡️ Modules requiring the STRING, ARRAY and VECTOR module. */
#include "modules/reflection.c"

/* ⚡️ION⚡️ Modules requiring the IO and REFLECTION modules. */
#include "modules/binary.c"
//#include "modules/csv.c"
#include "modules/json.c"

/* ⚡️ION⚡️ Modules requiring the IO module. */
#include "modules/tcp.c"


/* TODO: implement and organize these modules. */
#include "modules/http.c"
#include "modules/set.c"
