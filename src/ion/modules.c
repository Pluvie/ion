/* ⚡️ION⚡️ base module: required for every other module. */
#include "modules/core.c"

/* ⚡️ION⚡️ Modules requiring the CORE module only. */
#include "modules/array.c"
#include "modules/io.c"
#include "modules/map.c"
#include "modules/vector.c"
#include "modules/time.c"

/* ⚡️ION⚡️ Modules requiring the ARRAY module. */
#include "modules/string.c"

/* ⚡️ION⚡️ Modules requiring the STRING and VECTOR module. */
#include "modules/reflection.c"

/* ⚡️ION⚡️ Modules requiring the IO, REFLECTION, STRING, ARRAY and VECTOR modules. */
#include "modules/binary.c"
#include "modules/csv.c"
#include "modules/json.c"

/* ⚡️ION⚡️ Modules requiring the IO module. */
#include "modules/tcp.c"


/* TODO: implement and organize these modules. */
#include "modules/http.c"
#include "modules/range.c"
#include "modules/set.c"
#include "modules/tensor.c"
