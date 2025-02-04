void reflect_print (
    struct reflect* schema,
    char* name
)
{
  if (name != NULL)
    schema->name = name;

  print("");
  print_c(PRINT_COLOR_CYAN, "SCHEMA:");
  reflect_print_indentation(schema, 0);

  schema->name = NULL;
  return;
}
