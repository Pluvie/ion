#ifdef ION_INCLUDED
static inline
#endif

void string_to_number (
    struct string* string,
    enum types type,
    void* number
)
{
  errno = 0;

  char* last_parsed_char = NULL;
  u64 parsed_chars_count = 0;

  switch (type) {
  case U8:
  case U16:
  case U32:
  case U64:
    goto unsigned_integer_conversion;
  case I8:
  case I16:
  case I32:
  case I64:
    goto signed_integer_conversion;
  case D32:
  case D64:
  case D128:
    goto decimal_conversion;
  default:
    fail("cannot convert %.*s to (%s): type is not numeric",
      sp(string), type_names[type]);
    return;
  }

unsigned_integer_conversion:
  u64 unsigned_value = strtoull(string->content, &last_parsed_char, 0);

  parsed_chars_count = last_parsed_char - string->content;
  if (parsed_chars_count < string->length) {
    fail("cannot convert %.*s to (%s): invalid characters detected",
      sp(string), type_names[type]);
    return;
  }

  if (errno == ERANGE) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == U8 && unsigned_value > U8_MAX) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == U16 && unsigned_value > U16_MAX) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == U32 && unsigned_value > U32_MAX) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  }

  if (type == U8) {
    u8 unsigned_value_u8 = (u8) unsigned_value;
    memcpy(number, &unsigned_value_u8, sizeof(u8));
  } else if (type == U16) {
    u16 unsigned_value_u16 = (u16) unsigned_value;
    memcpy(number, &unsigned_value_u16, sizeof(u16));
  } else if (type == U32) {
    u32 unsigned_value_u32 = (u32) unsigned_value;
    memcpy(number, &unsigned_value_u32, sizeof(u32));
  } else if (type == U64) {
    u64 unsigned_value_u64 = (u64) unsigned_value;
    memcpy(number, &unsigned_value_u64, sizeof(u64));
  }

  return;

signed_integer_conversion:
  i64 signed_value = strtoll(string->content, &last_parsed_char, 0);

  parsed_chars_count = last_parsed_char - string->content;
  if (parsed_chars_count < string->length) {
    fail("cannot convert %.*s to (%s): invalid characters detected",
      sp(string), type_names[type]);
    return;
  }

  if (errno == ERANGE) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == I8 && (signed_value > I8_MAX || signed_value < I8_MIN)) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == I16 && (signed_value > I16_MAX || signed_value < I16_MIN)) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == I32 && (signed_value > I32_MAX || signed_value < I32_MIN)) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  }

  if (type == I8) {
    i8 signed_value_i8 = (i8) signed_value;
    memcpy(number, &signed_value_i8, sizeof(i8));
  } else if (type == I16) {
    i16 signed_value_i16 = (i16) signed_value;
    memcpy(number, &signed_value_i16, sizeof(i16));
  } else if (type == I32) {
    i32 signed_value_i32 = (i32) signed_value;
    memcpy(number, &signed_value_i32, sizeof(i32));
  } else if (type == I64) {
    i64 signed_value_i64 = (i64) signed_value;
    memcpy(number, &signed_value_i64, sizeof(i64));
  }

  return;

decimal_conversion:
  d128 decimal_value = strtold(string->content, &last_parsed_char);

  parsed_chars_count = last_parsed_char - string->content;
  if (parsed_chars_count < string->length) {
    fail("cannot convert %.*s to (%s): invalid characters detected",
      sp(string), type_names[type]);
    return;
  }

  if (errno == ERANGE) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == D32 && (decimal_value > D32_MAX || decimal_value < D32_MIN)) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  } else if (type == D64 && (decimal_value > D64_MAX || decimal_value < D64_MIN)) {
    fail("cannot convert %.*s to (%s): value overflow",
      sp(string), type_names[type]);
    return;
  }

  if (type == D32) {
    d32 decimal_value_d32 = (d32) decimal_value;
    memcpy(number, &decimal_value_d32, sizeof(d32));
  } else if (type == D64) {
    d64 decimal_value_d64 = (d64) decimal_value;
    memcpy(number, &decimal_value_d64, sizeof(d64));
  } else if (type == D128) {
    d128 decimal_value_d128 = (d128) decimal_value;
    memcpy(number, &decimal_value_d128, sizeof(d128));
  }

  return;
}
