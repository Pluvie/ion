static inline bool csv_is_reflection_compatible (
    struct reflection* rfx
)
{
  switch (rfx->type) {
  case ARRAY:
    goto check_element_is_struct;

  default:
    fail("unable to decode csv due to incompatible reflection: it must be an "
      "ARRAY of type STRUCT");
    return false;
  }

check_element_is_struct:
  struct reflection* element_rfx = rfx->element;

  if (element_rfx->type != STRUCT) {
    fail("unable to decode csv due to incompatible reflection: it must be an "
      "ARRAY of type STRUCT");
    return false;
  }

check_struct_not_nested:
  for vector_each(element_rfx->child, struct reflection*, field_rfx) {
    switch (field_rfx->type) {
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
    case STRING:
      continue;

    case BYTE:
    case CHAR:
    case STRUCT:
    case POINTER:
    case SEQUENCE:
    case ARRAY:
    case VECTOR:
      fail("unable to decode csv due to incompatible reflection: all fields of the "
        "struct must be numbers (I32, D64, U64, ecc.), BOOL, or STRING");
      return false;
    }
  }

  return true;
}
