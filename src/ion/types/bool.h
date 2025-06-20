#ifdef true
#undef true
#endif

#ifdef false
#undef false
#endif

#ifdef bool
#undef bool
#endif

#define bool uint32_t
#define true  ((bool) 1)
#define false ((bool) 0)
