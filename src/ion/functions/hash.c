/**
 * Predefined hash functions for ⚡️ION⚡️ base types. */

static inline int hash<int> (
    int value
)
{
  return value;
}

static inline int hash<dec> (
    dec value
)
{
  return (int) value;
}

static inline int hash<bool> (
    bool value
)
{
  return hash<int>((int) value);
}

static inline int hash<char> (
    char value
)
{
  return hash<int>((int) value);
}

static inline int hash<char*> (
    char* value
)
{
  return hash_djb2(value, strlen(value));
}

static inline int hash<string> (
    string value
)
{
  return hash_djb2(value.pointer, value.length);
}
