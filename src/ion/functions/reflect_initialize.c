static inline void reflect_initialize (
    struct reflect* reflection
)
{
  if (likely(reflection->initialized))
    return;

  for vector_each(reflection->child, struct reflect*, child) {
    child->parent = reflection;
    reflect_initialize(child);
  }

  reflection->initialized = true;
  return;
}
