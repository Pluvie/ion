#ifdef true
#undef true
#endif

#ifdef false
#undef false
#endif

#ifdef bool
#undef bool
#endif

#define bool int32
#define true  ((bool) 1)
#define false ((bool) 0)
