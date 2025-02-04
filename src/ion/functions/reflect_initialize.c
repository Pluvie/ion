static inline void reflect_initialize (
    struct reflect* schema
)
{
  if (likely(schema->initialized))
    return;

  print("init: %s", schema->name);
  for vector_each(schema->child, struct reflect*, child) {
    child->parent = schema;
    reflect_initialize(child);
  }

  schema->initialized = true;
  return;
}
