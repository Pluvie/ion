static inline bool json_discard_number_direct (
    struct io_direct* io
)
{
  #define cursor io->cursor
  #define STRING_TO_NUMBER__DISCARD
  #include "../procedures/string_to_number.c"
  #undef  STRING_TO_NUMBER__DISCARD
  #undef  cursor

procedure_success:
  return true;

procedure_failure:
  return false;
}



static inline bool json_discard_number_buffered (
    struct io_buffered* io
)
{
  io_reserve(io, 128);

  #define cursor io->cursor
  #define STRING_TO_NUMBER__DISCARD
  #include "../procedures/string_to_number.c"
  #undef  STRING_TO_NUMBER__DISCARD
  #undef  cursor

procedure_success:
  return true;

procedure_failure:
  return false;
}
