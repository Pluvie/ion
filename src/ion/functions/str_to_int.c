enum parse_number_results str_to_int (
    str* source,
    int* result
)
{
  #define PARSE_NUMBER__INTEGER
  #include "../procedures/parse_number.c"
}
