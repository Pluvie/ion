uint hash_djb2_cstr (
    cstr data
)
{
  uint hash = 5381;

  for (; *data != 0; data++)
    hash = ((hash << 5) + hash) + (*(byte*) data);

  return hash;
}
