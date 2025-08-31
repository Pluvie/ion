static inline void json_discard_string_direct (
    struct io_direct* io,
    string* result
)
#define JSON_DISCARD
#include "../procedures/json_parse_string.c"
#undef JSON_DISCARD



static inline void json_discard_string_buffered (
    struct io_buffered* io,
    string* result
)
#define JSON_DISCARD
#include "../procedures/json_parse_string.c"
#undef JSON_DISCARD
