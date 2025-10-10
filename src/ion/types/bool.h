#if standard(<= C17)
#undef true
#undef false

#define true  (bool) 1
#define false (bool) 0
#endif
