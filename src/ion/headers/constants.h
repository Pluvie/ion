#define ARRAY_DEFAULT_CAP     8




#define MAP_DEFAULT_CAP       8




#define MEMORY_DEFAULT_ALIGN  64
#define MEMORY_DEFAULT_CAP    64




#define PRINT_COLOR_RED       "\x1b[31m"
#define PRINT_COLOR_GREEN     "\x1b[32m"
#define PRINT_COLOR_YELLOW    "\x1b[33m"
#define PRINT_COLOR_BLUE      "\x1b[34m"
#define PRINT_COLOR_MAGENTA   "\x1b[35m"
#define PRINT_COLOR_CYAN      "\x1b[36m"
#define PRINT_COLOR_GREY      "\e[38;5;250m"
#define PRINT_COLOR_NONE      "\x1b[0m"




#define PROTO_NAME_MAX        88
#define PROTO_LEVEL_MAX       32




#define U8_MAX                UCHAR_MAX
#define U8_MIN                0
#define U16_MAX               USHRT_MAX
#define U16_MIN               0
#define U32_MAX               UINT_MAX
#define U32_MIN               0UL
#define U64_MAX               ULLONG_MAX
#define U64_MIN               0ULL
#define I8_MAX                SCHAR_MAX
#define I8_MIN                SCHAR_MIN
#define I8_MIN_ABS            ((u64) SCHAR_MAX) + 1
#define I16_MAX               SHRT_MAX
#define I16_MIN               SHRT_MIN
#define I16_MIN_ABS           ((u64) SHRT_MAX) + 1
#define I32_MAX               INT_MAX
#define I32_MIN               INT_MIN
#define I32_MIN_ABS           ((u64) INT_MAX) + 1
#define I64_MAX               LLONG_MAX
#define I64_MIN               LLONG_MIN
#define I64_MIN_ABS           ((u64) LLONG_MAX) + 1
#define D32_MAX               FLT_MAX
#define D32_MIN               -FLT_MAX
#define D32_MIN_ABS           FLT_MAX
#define D64_MAX               DBL_MAX
#define D64_MIN               -DBL_MAX
#define D64_MIN_ABS           DBL_MAX
#define D128_MAX              LDBL_MAX
#define D128_MIN              -LDBL_MAX
#define D128_MIN_ABS          LDBL_MAX
#define epsilon               DBL_EPSILON
