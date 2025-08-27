#ifdef int64
#undef int64
#endif

#ifdef int32
#undef int32
#endif

#ifdef int16
#undef int16
#endif

typedef int64_t   int64;
typedef int32_t   int32;
typedef int16_t   int16;

#ifdef  int
#undef  int
#endif

#define int int64
