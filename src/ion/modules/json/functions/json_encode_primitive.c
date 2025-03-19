static inline void json_encode_primitive (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  char number[1024] = { 0 };
  i32 printed_chars = 0;

  switch (rfx->type) {
  case U8:
    u8* obj_u8 = obj;
    printed_chars = snprintf(number, sizeof(number), "%u", *obj_u8);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case U16:
    u16* obj_u16 = obj;
    printed_chars = snprintf(number, sizeof(number), "%u", *obj_u16);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case U32:
    u32* obj_u32 = obj;
    printed_chars = snprintf(number, sizeof(number), "%u", *obj_u32);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case U64:
    u64* obj_u64 = obj;
    printed_chars = snprintf(number, sizeof(number), "%lu", *obj_u64);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case I8:
    i8* obj_i8 = obj;
    printed_chars = snprintf(number, sizeof(number), "%i", *obj_i8);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case I16:
    i16* obj_i16 = obj;
    printed_chars = snprintf(number, sizeof(number), "%i", *obj_i16);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case I32:
    i32* obj_i32 = obj;
    printed_chars = snprintf(number, sizeof(number), "%i", *obj_i32);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case I64:
    i64* obj_i64 = obj;
    printed_chars = snprintf(number, sizeof(number), "%li", *obj_i64);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case D32:
    d32* obj_d32 = obj;
    printed_chars = snprintf(number, sizeof(number), "%f", *obj_d32);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case D64:
    d64* obj_d64 = obj;
    printed_chars = snprintf(number, sizeof(number), "%f", *obj_d64);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case D128:
    d128* obj_d128 = obj;
    printed_chars = snprintf(number, sizeof(number), "%Lf", *obj_d128);
    if (printed_chars >= sizeof(number))
      printed_chars = sizeof(number) - 1;

    io_write(io, number, printed_chars);
    return;

  case BOOL:
    bool* obj_bool = obj;
    if (*obj_bool)
      io_write(io, "true", lengthof("true"));
    else
      io_write(io, "false", lengthof("false"));

    return;

  case BYTE:
  case CHAR:
    fail("primitive type `%s` not supported in json", type_names[rfx->type]);
    error_add_io_extraction(io);
    error_add_reflection_path(rfx);
    return;

  default:
    return;
  }
}
