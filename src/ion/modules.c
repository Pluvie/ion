/* ⚡️ION⚡️ base module: required for every other module. */
#include "modules/core.c"

/* ⚡️ION⚡️ Modules requiring the CORE module only. */
#include "modules/array.c"
//#include "modules/io.c"
#include "modules/map.c"
#include "modules/set.c"
#include "modules/time.c"

/* ⚡️ION⚡️ Modules requiring the ARRAY module. */
//#include "modules/reflection.c"
#include "modules/tensor.c"

/* ⚡️ION⚡️ Modules requiring the IO and REFLECTION modules. */
//#include "modules/binary.c"
//#include "modules/csv.c"
//#include "modules/json.c"

/* ⚡️ION⚡️ Modules requiring the IO module. */
//#include "modules/tcp.c"

/* ⚡️ION⚡️ Modules requiring the TCP module. */
//#include "modules/http.c"
