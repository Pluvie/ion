/*
struct N container_function(N, alloc) (
    uint initial_capacity,
    struct arena* allocator
);
*/

T* container_function(N, at) (
    struct N* list,
    uint position
);

/*
uint container_function(N, del) (
    struct N* list,
    T element
);

bool container_function(N, each) (
    struct N* list,
    struct iterator* iter
);

struct N container_function(N, init) (
    uint capacity,
    T* data
);

T* container_function(N, pop) (
    struct N* list
);
*/

uint container_function(N, push) (
    struct N* list,
    T element
);

/*
void container_function(N, sort) (
    struct N* list,
    int (*comparator)(const void* a, const void* b)
);
*/
