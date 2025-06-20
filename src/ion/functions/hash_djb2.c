int hash_djb2 (
    void* data,
    int length
)
{
  int hash = 5381;

  for (int i = 0; i < length; i++)
    hash = ((hash << 5) + hash) + ((unsigned char*) data)[i];

  return hash;
}
