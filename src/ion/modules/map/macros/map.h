/**
 * Defines a map type declination. */
#define map(...)              _map(__VA_ARGS__)
#define _map(k, v)            map__ ## k ## __ ## v

/* Defines all map declined declined symbols. */
#define map_allocate(...)     _map_allocate(__VA_ARGS__)
#define _map_allocate(k, v)   map_allocate__ ## k ## __ ## v
#define map_init(...)         _map_init(__VA_ARGS__)
#define _map_init(k, v)       map_init__ ## k ## __ ## v
#define map_get(...)          _map_get(__VA_ARGS__)
#define _map_get(k, v)        map_get__ ## k ## __ ## v
#define map_set(...)          _map_set(__VA_ARGS__)
#define _map_set(k, v)        map_set__ ## k ## __ ## v
#define map_del(...)          _map_del(__VA_ARGS__)
#define _map_del(k, v)        map_del__ ## k ## __ ## v
#define map_rehash(...)       _map_rehash(__VA_ARGS__)
#define _map_rehash(k, v)     map_rehash__ ## k ## __ ## v
#define map_comparer(...)     _map_comparer(__VA_ARGS__)
#define _map_comparer(k, v)   map_comparer__ ## k ## __ ## v
#define map_hasher(...)       _map_hasher(__VA_ARGS__)
#define _map_hasher(k, v)     map_hasher__ ## k ## __ ## v
#define map_iterator(...)     _map_iterator(__VA_ARGS__)
#define _map_iterator(k, v)   map_iterator__ ## k ## __ ## v
