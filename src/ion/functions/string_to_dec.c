dec string_to_dec (
    string* source
)
{
  dec result = 0;
  #define STRING_TO_NUMBER__DECIMAL
  #include "../procedures/string_to_number.c"
  #undef  STRING_TO_NUMBER__DECIMAL

procedure_success:
  return result;

procedure_failure:
  return 0;
}
