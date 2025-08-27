/**
 * Predefined hash functions for ⚡️ION⚡️ base types. */

int hash<int> (
    int value
)
{
  return value;
}

int hash<dec> (
    dec value
)
{
  return (int) value;
}

int hash<bool> (
    bool value
)
{
  return hash<int>((int) value);
}

int hash<char> (
    char value
)
{
  return hash<int>((int) value);
}

int hash<char*> (
    char* value
)
{
  return hash_djb2(value, strlen(value));
}

int hash<string> (
    string value
)
{
  return hash_djb2(value.pointer, value.length);
}
