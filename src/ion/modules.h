/* ⚡️ION⚡️ base module: required for every other module. */
#include "modules/core.h"

/* ⚡️ION⚡️ Modules requiring the CORE module only. */
#include "modules/array.h"
#include "modules/date.h"
#include "modules/io.h"
#include "modules/map.h"
#include "modules/vector.h"

/* ⚡️ION⚡️ Modules requiring the ARRAY module. */
#include "modules/string.h"

/* ⚡️ION⚡️ Modules requiring the STRING, ARRAY and VECTOR module. */
#include "modules/reflection.h"

/* ⚡️ION⚡️ Modules requiring the IO and REFLECTION modules. */
#include "modules/binary.h"
//#include "modules/csv.h"
#include "modules/json.h"


/* TODO: organize these modules. */
#include "modules/http.h"
#include "modules/range.h"
#include "modules/set.h"
#include "modules/tcp.h"
#include "modules/tensor.h"
#include "modules/time.h"
