bool container_function(N, has) (
    struct N* map,
    K key
)
{
  return container_function(S, has)(&map->keys, key);
}
