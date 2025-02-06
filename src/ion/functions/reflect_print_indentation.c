void reflect_print_indentation (
    struct reflect* reflection,
    u32 indentation
)
{
  for (u32 i = 0; i < indentation; i++)
    emit(" ");

  switch (reflection->type) {
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
    print("%s : %s", reflection->name, type_names[reflection->type]);
    break;

  case STRUCT:
    print("%s : struct", reflection->name);
    for vector_each(reflection->child, struct reflect*, field)
      reflect_print_indentation(field, indentation + 2);
    break;

  case POINTER:
    print("%s : pointer", reflection->name);
    reflect_print_indentation(vector_get(reflection->child, 0), indentation + 2);
    break;

  case SEQUENCE:
    print("%s : sequence", reflection->name);
    reflect_print_indentation(vector_get(reflection->child, 0), indentation + 2);
    break;

  case ARRAY:
    print("%s : array", reflection->name);
    reflect_print_indentation(vector_get(reflection->child, 0), indentation + 2);
    break;

  case VECTOR:
    print("%s : vector", reflection->name);
    reflect_print_indentation(vector_get(reflection->child, 0), indentation + 2);
    break;
  }
}
