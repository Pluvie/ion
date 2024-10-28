static inline bool reflect_validate (
    struct reflect* schema,
    void* value
)
{
  if (schema->validator == NULL)
    return true;

  return schema->validator(value, schema);
}
