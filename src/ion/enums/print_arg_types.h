/*
  Defines all automatic printable types through the macros `print`, `printl`, `prints`
  and the likes of it.
*/
enum print_arg_types {
  PRINT_ARG__INT0     = 0,
  PRINT_ARG__INT      = 1,
  PRINT_ARG__UINT     = 2,
  PRINT_ARG__DEC      = 3,
  PRINT_ARG__STR      = 4,
  PRINT_ARG__BOOL     = 5,
  PRINT_ARG__CHAR     = 6,
  PRINT_ARG__UCHAR    = 7,
  PRINT_ARG__CHAR_P   = 8,
  PRINT_ARG__VOID_P   = 9,
};
