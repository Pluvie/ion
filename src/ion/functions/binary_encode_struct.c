static inline void binary_encode_struct (
    struct object* source,
    struct io* target
)
{
  for vector_each(source->schema->child, struct reflect*, field) {
    struct object field_object = {
      .schema = field,
      .address = source->address + field->offset
    };
    binary_encode(&field_object, target);
    if (error.occurred)
      return;
  }
}
