static inline void binary_encode_primitive (
    struct object* source,
    struct io* target
)
{
  u32 type_size = type_sizes[source->reflection->type];

  io_write(target, source->address, type_size);
  if (error.occurred)
    return error_add_reflection_path(source->reflection);
}
