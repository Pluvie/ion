void reflection_inspect_value (
    struct reflection* rfx,
    void* object,
    u32 indentation
)
{
  if (object == NULL) {
    emit(": ");
    print_c(PRINT_COLOR_CYAN, "nil");
    return;
  }

  switch (rfx->type) {
  case U8:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%u", *(u8*) object);
    break;
  case U16:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%u", *(u16*) object);
    break;
  case U32:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%u", *(u32*) object);
    break;
  case U64:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%lu", *(u64*) object);
    break;
  case I8:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%i", *(i8*) object);
    break;
  case I16:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%i", *(i16*) object);
    break;
  case I32:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%i", *(i32*) object);
    break;
  case I64:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%li", *(i64*) object);
    break;
  case D32:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%f", *(d32*) object);
    break;
  case D64:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%f", *(d64*) object);
    break;
  case D128:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%Lf", *(d128*) object);
    break;
  case BYTE:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%02x", *(byte*) object);
    break;
  case CHAR:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%c", *(char*) object);
    break;
  case BOOL:
    emit(": ");
    print_c(PRINT_COLOR_GREEN, "%s", *(bool*) object ? "true" : "false");
    break;

  case STRING:
    emit(": ");
    print_c(PRINT_COLOR_YELLOW, "\"%.*s\"", sp(((struct string*) object)));
    break;

  case STRUCT:
    emit(": ");
    print("{");

    for vector_each(rfx->fields, struct reflection*, field_rfx) {
      field_rfx->parent = rfx;
      void* field = object + field_rfx->offset;
      reflection_inspect_indentation(field_rfx, field, indentation + 2);
    }

    for (u32 i = 0; i < indentation; i++) emit(" ");
    print("}");
    break;

  case POINTER:
    void* element = *(void**) object;
    reflection_inspect_indentation(rfx->element, element, indentation + 2);
    break;

  case SEQUENCE:
    emit(": ");
    print("{");

    u64 length = rfx->size / rfx->element->size;
    for (u64 i = 0; i < length; i++) {
      void* element = object + (i * rfx->element->size);
      reflection_inspect_indentation(rfx->element, element, indentation + 2);
    }

    for (u32 i = 0; i < indentation; i++) emit(" ");
    print("}");
    break;

  case ARRAY:
    emit(": ");
    struct array* array = (struct array*) object;
    if (array->length == 0) {
      print("[]");
      break;
    }

    print("[");

    for array_each(array, void*, element)
      reflection_inspect_indentation(rfx->element, element, indentation + 2);

    for (u32 i = 0; i < indentation; i++) emit(" ");
    print("]");
    break;

  case VECTOR:
    emit(": ");
    struct vector* vector = (struct vector*) object;
    if (vector->length == 0) {
      print("[]");
      break;
    }

    print("[");

    for vector_each(vector, void*, element)
      reflection_inspect_indentation(rfx->element, element, indentation + 2);

    for (u32 i = 0; i < indentation; i++) emit(" ");
    print("]");
    break;
  }
}
