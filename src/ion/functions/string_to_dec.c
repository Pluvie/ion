dec string_to_dec (
    string* source
)
{
  dec result = 0;
  char* cursor = source->chars;

  #define PARSE_NUMBER__DECIMAL
  #include "../procedures/parse_number.c"
  #undef  PARSE_NUMBER__DECIMAL

procedure_success:
  return result;

procedure_failure:
  return 0;
}
