void reflect_print (
    struct reflect* schema
)
{
  print("");
  print_c(PRINT_COLOR_CYAN, "SCHEMA:");
  reflect_print_indentation(schema, 0);
}
