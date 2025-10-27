uint hash_djb2 (
    void* data,
    uint length
)
{
  uint hash = 5381;
  uint i;

  for (i = 0; i < length; i++)
    hash = ((hash << 5) + hash) + ((byte*) data)[i];

  return hash;
}
