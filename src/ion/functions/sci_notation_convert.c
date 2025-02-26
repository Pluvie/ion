#ifdef ION_INCLUDED
static inline
#endif

void sci_notation_convert (
    struct sci_notation* number,
    enum types type,
    void* result
)
{
  bool unsigned_type  = type >= U8  && type <= U64;
  bool signed_type    = type >= I8  && type <= I64;
  bool decimal_type   = type >= D32 && type <= D128;

  u32 number_length = number->integral.length +
    number->fractional.length +
    number->exponent.length;
  if (!unsigned_type)
    number_length++;
  if (number->fractional.length > 0)
    number_length++;
  if (number->exponent.length > 0)
    number_length += 2;
  char number_string[number_length + 1];

consistency_checks:
  if (unsigned_type && number->negative) {
    fail("cannot convert to (%s): number is negative", type_names[type]);
    return;
  }

  if (!decimal_type && number->fractional.length > 0) {
    fail("cannot convert to (%s): number is fractional", type_names[type]);
    return;
  }

  if (!decimal_type && number->exponent.length > 0) {
    fail("cannot convert to (%s): number has an exponent", type_names[type]);
    return;
  }

  if (unsigned_type)  goto unsigned_conversion;
  if (signed_type)    goto signed_conversion;
  if (decimal_type)   goto decimal_conversion;

  fail("cannot convert to (%s): type is not numeric", type_names[type]);
  return;

unsigned_conversion:
  snprintf(number_string, number_length + 1, "%.*s",
    number->integral.length, number->integral.content);

  errno = 0;
  u64 unsigned_value = strtoull(number_string, NULL, 10);

  if (errno == ERANGE) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == U8 && unsigned_value > U8_MAX) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == U16 && unsigned_value > U16_MAX) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == U32 && unsigned_value > U32_MAX) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  }

  if (type == U8) {
    u8 unsigned_value_u8 = (u8) unsigned_value;
    memcpy(result, &unsigned_value_u8, sizeof(u8));
  } else if (type == U16) {
    u16 unsigned_value_u16 = (u16) unsigned_value;
    memcpy(result, &unsigned_value_u16, sizeof(u16));
  } else if (type == U32) {
    u32 unsigned_value_u32 = (u32) unsigned_value;
    memcpy(result, &unsigned_value_u32, sizeof(u32));
  } else if (type == U64) {
    u64 unsigned_value_u64 = (u64) unsigned_value;
    memcpy(result, &unsigned_value_u64, sizeof(u64));
  }

  return;

signed_conversion:
  snprintf(number_string, number_length + 1, "%c%.*s",
    number->negative ? '-' : '+',
    number->integral.length, number->integral.content);

  errno = 0;
  i64 signed_value = strtoll(number_string, NULL, 10);

  if (errno == ERANGE) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == I8 && (signed_value > I8_MAX || signed_value < I8_MIN)) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == I16 && (signed_value > I16_MAX || signed_value < I16_MIN)) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == I32 && (signed_value > I32_MAX || signed_value < I32_MIN)) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  }

  if (type == I8) {
    i8 signed_value_i8 = (i8) signed_value;
    memcpy(result, &signed_value_i8, sizeof(i8));
  } else if (type == I16) {
    i16 signed_value_i16 = (i16) signed_value;
    memcpy(result, &signed_value_i16, sizeof(i16));
  } else if (type == I32) {
    i32 signed_value_i32 = (i32) signed_value;
    memcpy(result, &signed_value_i32, sizeof(i32));
  } else if (type == I64) {
    i64 signed_value_i64 = (i64) signed_value;
    memcpy(result, &signed_value_i64, sizeof(i64));
  }

  return;

decimal_conversion:
  if (number->exponent.length > 0)
    snprintf(number_string, number_length + 1, "%c%.*s.%.*se%c%.*s",
      number->negative ? '-' : '+',
      number->integral.length, number->integral.content,
      number->fractional.length, number->fractional.content,
      number->negative_exponent ? '-' : '+',
      number->exponent.length, number->exponent.content);
  else
    snprintf(number_string, number_length + 1, "%c%.*s.%.*s",
      number->negative ? '-' : '+',
      number->integral.length, number->integral.content,
      number->fractional.length, number->fractional.content);

  errno = 0;
  d128 decimal_value = strtold(number_string, NULL);

  if (errno == ERANGE) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == D32 && (decimal_value > D32_MAX || decimal_value < D32_MIN)) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  } else if (type == D64 && (decimal_value > D64_MAX || decimal_value < D64_MIN)) {
    fail("cannot convert %s to (%s): value overflow",
      number_string, type_names[type]);
    return;
  }

  if (type == D32) {
    d32 decimal_value_d32 = (d32) decimal_value;
    memcpy(result, &decimal_value_d32, sizeof(d32));
  } else if (type == D64) {
    d64 decimal_value_d64 = (d64) decimal_value;
    memcpy(result, &decimal_value_d64, sizeof(d64));
  } else if (type == D128) {
    d128 decimal_value_d128 = (d128) decimal_value;
    memcpy(result, &decimal_value_d128, sizeof(d128));
  }
}
