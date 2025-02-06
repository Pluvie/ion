void reflect_print (
    struct reflect* reflection,
    char* name
)
{
  if (name != NULL)
    reflection->name = name;

  print("");
  print_c(PRINT_COLOR_CYAN, "SCHEMA:");
  reflect_print_indentation(reflection, 0);

  reflection->name = NULL;
  return;
}
