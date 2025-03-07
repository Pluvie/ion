void reflection_print_indentation (
    struct reflection* rfx,
    u32 indentation
)
{
  for (u32 i = 0; i < indentation; i++)
    emit(" ");

  if (rfx->name == NULL)
    emit("- : %s", type_names[rfx->type]);
  else
    emit("%.*s : %s", sp(rfx->name), type_names[rfx->type]);

  print(" [%li] {%li}", rfx->size, rfx->offset);

  switch (rfx->type) {
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
  case STRING:
    break;

  case STRUCT:
    for vector_each(rfx->fields, struct reflection*, field)
      reflection_print_indentation(field, indentation + 2);
    break;

  case POINTER:
    reflection_print_indentation(rfx->element, indentation + 2);
    break;

  case SEQUENCE:
    reflection_print_indentation(rfx->element, indentation + 2);
    break;

  case ARRAY:
    reflection_print_indentation(rfx->element, indentation + 2);
    break;

  case VECTOR:
    reflection_print_indentation(rfx->element, indentation + 2);
    break;
  }
}
