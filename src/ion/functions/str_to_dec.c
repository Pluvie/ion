enum result str_to_dec (
    str* source,
    dec* result
)
{
  #define PARSE_NUMBER__DECIMAL
  #include "../procedures/parse_number.c"
}
