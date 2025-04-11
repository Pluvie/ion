/**
 * Defines an array type declination. */
#define array(...)              _array(__VA_ARGS__)
#define _array(t)               array__ ## t

/* Defines an array type declination identifier. */
#define array_(...)             _array_(__VA_ARGS__)
#define _array_(i, t)           array_ ## i ## __ ## t

/* Defines all array operations. */
#define array_allocate(...)     _array_allocate(__VA_ARGS__)
#define _array_allocate(t)      array_allocate__ ## t
#define array_init(...)         _array_init(__VA_ARGS__)
#define _array_init(t)          array_init__ ## t
#define array_get(...)          _array_get(__VA_ARGS__)
#define _array_get(t)           array_get__ ## t
#define array_set(...)          _array_set(__VA_ARGS__)
#define _array_set(t)           array_set__ ## t
#define array_pop(...)          _array_pop(__VA_ARGS__)
#define _array_pop(t)           array_pop ## t
#define array_push(...)         _array_push(__VA_ARGS__)
#define _array_push(t)          array_push__ ## t
#define array_last(...)         _array_last(__VA_ARGS__)
#define _array_last(t)          array_last ## t
