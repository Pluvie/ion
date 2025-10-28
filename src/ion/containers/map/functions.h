#include "functions/map_each.h"
#include "functions/map_init.h"
#include "functions/map_set.h"

struct N container_function(N, alloc) (
    uint initial_capacity,
    struct allocator* allocator
);

V* container_function(N, del) (
    struct N* map,
    K key
);

V* container_function(N, get) (
    struct N* map,
    K key
);

bool container_function(N, has) (
    struct N* map,
    K key
);

/*
struct N container_function(N, literal) (
    uint capacity,
    K* keys,
    V* values,
    uint* hashes,
    void* pairs
);
*/
