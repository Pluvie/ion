static inline bool csv_is_reflection_compatible (
    struct reflect* reflection
)
{
  switch (reflection->type) {
  case ARRAY:
    goto check_element_is_struct;

  default:
    fail("unable to decode csv due to incompatible reflection: it must be an "
      "ARRAY of type STRUCT");
    return false;
  }

check_element_is_struct:
  struct reflect* element = vector_get(reflection->child, 0);

  if (element->type != STRUCT) {
    fail("unable to decode csv due to incompatible reflection: it must be an "
      "ARRAY of type STRUCT");
    return false;
  }

check_struct_not_nested:
  for vector_each(element->child, struct reflect*, field_reflection) {
    switch (field_reflection->type) {
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
    case BOOL:
      continue;

    case POINTER:
      struct reflect* pointer_reflection = vector_get(field_reflection->child, 0);
      if (pointer_reflection->type != CHAR) {
        fail("unable to decode csv due to incompatible reflection: all fields of the "
          "struct must be numbers, BOOL, or POINTER of type CHAR");
        return false;
      }
      continue;

    case BYTE:
    case CHAR:
    case STRUCT:
    case SEQUENCE:
    case ARRAY:
    case VECTOR:
      fail("unable to decode csv due to incompatible reflection: all fields of the "
        "struct must be numbers, BOOL, or POINTER of type CHAR");
      return false;
    }
  }

  return true;
}
