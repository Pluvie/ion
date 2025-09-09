static inline void json_decode_dec_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
)
{
  dec result = 0;
  #define cursor io->cursor
  #define STRING_TO_NUMBER__DECIMAL
  #include "../procedures/string_to_number.c"
  #undef  STRING_TO_NUMBER__DECIMAL
  #undef  cursor

procedure_success:
  if (unlikely(!reflection_validate(rfx, &result)))
    goto procedure_failure;

  byte_copy(target, &result, sizeof(dec));
  return;

procedure_failure:
  failure_add_io_info(io);
  failure_add_reflection_info(rfx);
  return;
}



static inline void json_decode_dec_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
)
{
  io_reserve(io, 128);

  dec result = 0;
  #define cursor io->cursor
  #define STRING_TO_NUMBER__DECIMAL
  #include "../procedures/string_to_number.c"
  #undef  STRING_TO_NUMBER__DECIMAL
  #undef  cursor

procedure_success:
  if (unlikely(!reflection_validate(rfx, &result)))
    goto procedure_failure;

  byte_copy(target, &result, sizeof(dec));
  return;

procedure_failure:
  failure_add_io_info(io);
  failure_add_reflection_info(rfx);
  return;
}
