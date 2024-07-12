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
  case ARRAY:
    return sizeof(struct array);
  case STRUCT:
    return schema->bounds[0];
  case POINTER:
    return sizeof(void*);
  case SEQUENCE:
    return schema->bounds[0] * reflect_typesize(schema->child);
  }

  return 0;
}
