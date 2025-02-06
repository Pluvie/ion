static inline bool reflect_validate (
    struct reflect* reflection,
    void* value
)
{
  if (reflection->validator == NULL)
    return true;

  return reflection->validator(value, reflection);
}
