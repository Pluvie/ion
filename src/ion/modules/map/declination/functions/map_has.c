bool map_has(kt, vt) (
    map(kt, vt)* m,
    kt* key
)
{
  return map_get(kt, vt)(m, key) != NULL;
}
