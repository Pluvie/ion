struct N container_function(N, alloc) (
    uint initial_capacity,
    struct allocator* allocator
);

V* container_function(N, del) (
    struct N* map,
    K key
);

/*
bool container_function(N, each) (
    struct N* map,
    struct iterator* iter
);
*/

V* container_function(N, get) (
    struct N* map,
    K key
);

bool container_function(N, has) (
    struct N* map,
    K key
);

/*
struct N container_function(N, init) (
    uint capacity,
    K* keys,
    V* values,
    uint* hashes
);

struct N container_function(N, literal) (
    uint capacity,
    K* keys,
    V* values,
    uint* hashes,
    void* pairs
);
*/

uint container_function(N, set) (
    struct N* map,
    K key,
    V value
);
