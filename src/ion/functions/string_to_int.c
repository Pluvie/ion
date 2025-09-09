int string_to_int (
    string* source
)
{
  int result = 0;
  char* cursor = source->pointer;
  #define STRING_TO_NUMBER__INTEGER
  #include "../procedures/string_to_number.c"
  #undef  STRING_TO_NUMBER__INTEGER

procedure_success:
  return result;

procedure_failure:
  return 0;
}
