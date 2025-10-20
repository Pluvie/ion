#if standard(< C23)
#undef  true
#define true  (bool) 1

#undef  false
#define false (bool) 0
#endif
