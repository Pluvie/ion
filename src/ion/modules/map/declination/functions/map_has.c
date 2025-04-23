bool map_has(kt, vt) (
    map(kt, vt)* map,
    kt* key
)
{
  return map_get(kt, vt)(map, key) != NULL;
}
