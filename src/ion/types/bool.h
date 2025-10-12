#if standard(< C23)
check_sizeof(1, bool);

#undef true
#undef false

#define true  (bool) 1
#define false (bool) 0
#endif
