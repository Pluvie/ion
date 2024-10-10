void reflect_print_indentation (
    struct reflect* schema,
    u32 indentation
)
{
  for (u32 i = 0; i < indentation; i++)
    emit(" ");

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
    print("%s : %s", schema->name, type_names[schema->type]);
    break;

  case STRUCT:
    print("%s : struct", schema->name);
    for (u32 i = 0; i < schema->bounds[1]; i++)
      reflect_print_indentation(schema->child + i, indentation + 2);

    break;

  case ARRAY:
    print("%s : array", schema->name);
    reflect_print_indentation(schema->child, indentation + 2);
    break;

  case POINTER:
    print("%s : pointer", schema->name);
    reflect_print_indentation(schema->child, indentation + 2);
    break;

  case SEQUENCE:
    print("%s : sequence", schema->name);
    reflect_print_indentation(schema->child, indentation + 2);
    break;
  }
}
