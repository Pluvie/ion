void reflection_inspect_type (
    struct reflection* rfx
)
{
  switch (rfx->type) {
  case U8:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "u8");
    break;
  case U16:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "u16");
    break;
  case U32:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "u32");
    break;
  case U64:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "u64");
    break;
  case I8:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "i8");
    break;
  case I16:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "i16");
    break;
  case I32:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "i32");
    break;
  case I64:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "i64");
    break;
  case D32:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "d32");
    break;
  case D64:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "d64");
    break;
  case D128:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "d128");
    break;
  case BYTE:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "byte");
    break;
  case CHAR:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "char");
    break;
  case BOOL:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "bool");
    break;

  case STRING:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "string");
    break;

  case STRUCT:
    emit("[");
    if (rfx->struct_name != NULL) {
      emit_c(PRINT_COLOR_MAGENTA, "%.*s", sp(rfx->struct_name));
    } else {
      emit_c(PRINT_COLOR_MAGENTA, "struct");
    }
    break;

  case POINTER:
    rfx->element->parent = rfx;
    return;

  case SEQUENCE:
    rfx->element->parent = rfx;
    rfx->length = rfx->size / rfx->element->size;
    emit("[");
    emit_c(PRINT_COLOR_GREEN, "%li", rfx->length);
    break;

  case ARRAY:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "array");
    break;

  case VECTOR:
    emit("[");
    emit_c(PRINT_COLOR_MAGENTA, "vector");
    break;

  default:
    return;
  }

  struct reflection* pointer = rfx->parent;
  while (pointer != NULL && pointer->type == POINTER) {
    emit_c(PRINT_COLOR_CYAN, "*");
    pointer = pointer->parent;
  }

  emit("]");
}
