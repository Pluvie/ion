/**
 * Defines a set type declination. */
#define set(...)              _set(__VA_ARGS__)
#define _set(t)               set__ ## t

/* Defines all set declined declined symbols. */
#define set_allocate(...)     _set_allocate(__VA_ARGS__)
#define _set_allocate(t)      set_allocate__ ## t
#define set_init(...)         _set_init(__VA_ARGS__)
#define _set_init(t)          set_init__ ## t
#define set_add(...)          _set_add(__VA_ARGS__)
#define _set_add(t)           set_add__ ## t
#define set_has(...)          _set_has(__VA_ARGS__)
#define _set_has(t)           set_has__ ## t
#define set_del(...)          _set_del(__VA_ARGS__)
#define _set_del(t)           set_del__ ## t
#define set_rehash(...)       _set_rehash(__VA_ARGS__)
#define _set_rehash(t)        set_rehash__ ## t
#define set_comparer(...)     _set_comparer(__VA_ARGS__)
#define _set_comparer(t)      set_comparer__ ## t
#define set_hasher(...)       _set_hasher(__VA_ARGS__)
#define _set_hasher(t)        set_hasher__ ## t
#define set_iterator(...)     _set_iterator(__VA_ARGS__)
#define _set_iterator(t)      set_iterator__ ## t
