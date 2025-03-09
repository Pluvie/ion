/* ⚡️ION⚡️ base module: required for every other module. */
#include "modules/core.h"

/* ⚡️ION⚡️ Modules requiring the CORE module only. */
#include "modules/array.h"
#include "modules/io.h"
#include "modules/map.h"
#include "modules/string.h"
#include "modules/vector.h"
#include "modules/time.h"

/* ⚡️ION⚡️ Modules requiring the VECTOR module. */
#include "modules/tensor.h"

/* ⚡️ION⚡️ Modules requiring the STRING, ARRAY and VECTOR module. */
#include "modules/reflection.h"

/* ⚡️ION⚡️ Modules requiring the IO and REFLECTION modules. */
#include "modules/binary.h"
#include "modules/csv.h"
#include "modules/json.h"


/* TODO: implement and organize these modules. */
#include "modules/http.h"
#include "modules/range.h"
#include "modules/set.h"
#include "modules/tcp.h"
