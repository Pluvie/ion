bool container_function(N, each) (
    struct N* map,
    struct iterator* iter
#if standard(== C89)
  , K** key_ptr,
    V** value_ptr
#endif
);
