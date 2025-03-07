void reflection_print (
    struct reflection* rfx,
    struct string* name
)
{
  if (name != NULL)
    rfx->name = name;

  print("");
  print_c(PRINT_COLOR_CYAN, "SCHEMA:");
  reflection_print_indentation(rfx, 0);

  rfx->name = NULL;
  return;
}
