static inline u32 reflect_typesize (
    struct reflect* schema
)
{
  switch (schema->type) {
  case U8:
  case U16:
  case U32:
  case U64:
  case I8:
  case I16:
  case I32:
  case I64:
  case D32:
  case D64:
  case D128:
  case BYTE:
  case CHAR:
  case BOOL:
    return type_sizes[schema->type];
  case STRUCT:
    return schema->bounds[0];
  case POINTER:
    return sizeof(void*);
  case SEQUENCE:
    return schema->bounds[0] * reflect_typesize(vector_get(schema->child, 0));
  case ARRAY:
    return sizeof(struct array);
  case VECTOR:
    return sizeof(struct vector);
  }

  return 0;
}
