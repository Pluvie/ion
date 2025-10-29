enum parse_number_results str_to_dec (
    str* source,
    dec* result
)
{
  #define PARSE_NUMBER__DECIMAL
  #include "../procedures/parse_number.c"
}
