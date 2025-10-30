#include "functions/set_add.h"
#include "functions/set_init.h"
#include "functions/set_literal.h"

struct N container_function(N, alloc) (
    uint initial_capacity,
    struct allocator* allocator
);

uint container_function(N, del) (
    struct N* set,
    T element
);

/*
bool container_function(N, each) (
    N* set,
    struct iterator* iter
);
*/

bool container_function(N, has) (
    struct N* set,
    T element
);

uint container_function(N, pos) (
    struct N* set,
    T element
);

void container_function(N, rehash) (
    struct N* set
);
