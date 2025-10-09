unsigned int hash_djb2_cstr (
    char* data
)
{
  unsigned int hash = 5381;

  for (; *data != 0; data++)
    hash = ((hash << 5) + hash) + (*(unsigned char*) data);

  return hash;
}
