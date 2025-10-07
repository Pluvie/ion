int string_to_int (
    string* source
)
{
  int result = 0;
  char* cursor = source->chars;

  #define PARSE_NUMBER__INTEGER
  #include "../procedures/parse_number.c"
  #undef  PARSE_NUMBER__INTEGER

procedure_success:
  return result;

procedure_failure:
  return 0;
}
