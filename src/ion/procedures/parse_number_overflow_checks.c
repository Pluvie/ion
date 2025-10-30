
  if (unlikely(number_length > INT_MAXCHARS)) {
    /* If the number length is greater than the maximum chars that can be contained
      in an integer, and we have only an integral part, then we have an overflow for
      sure. For example, on 32-bit systems, the maximum number of chars in an integer
      is 10: the highest integer is infact 2147483647 (2^32 - 1), which is 10
      characters long. So if we end up having 11 or more chars, all of which
      representing an integral number with no decimal part, we have overflowed. */
    if (decimal_length == 0)
      return fail("number overflow");

    /* If we have a decimal part, and the integral part is '0', we can parse as
      many extra digits as we have leading zeroes in the decimal part. For example,
      in a 64-bit system, the number 0.00000789789789789789 has 21 digits, which are
      more than the INT_MAXCHARS (19 in 64-bit) but it won't overflow because all the
      zero multiplications do not increase the number value until finding the first
      non-zero digit. */
    if (decimal_length > 0) {
      int leading_zeros = 0;

      if (*integral_start == '0') {
        int i;
        leading_zeros++;

        for (i = 0; i < decimal_length; i++) {
          if (decimal_start[i] != '0')
            break;
          leading_zeros++;
        }
      }

      if (number_length - leading_zeros > INT_MAXCHARS)
        return fail("number overflow");
    }

  } else if (unlikely(number_length == INT_MAXCHARS)) {
    /* If the number length is equal than the maximum chars of an integer, we have an
      overflow only if the number is greater than INT_MAXNUM constant.

      Suppose the number is 9999900.009 and we are on a 32-bit system. This number
      overflows because it is exactly 10 digits long (7 for the integral part and 3
      for the decimal part) and when multiplicating the last digit -- with the
      accumulator technique in `parse_digit.c` -- an overflow occurs, because
      999990000 * 9 is greater than the maximum 32-bit integer 2147483647.

      We then compare the integral part and the decimal part (if present) char by char
      with the INT_MAXNUM constant, and if the comparison shows that at least one char
      is greater than the corresponding char in INT_MAXNUM, then we have an overflow. */
    if (memory_compare(integral_start, INT_MAXNUM, integral_length) > 0)
      return fail("number overflow");

    if (decimal_length > 0) {
      cstr integral_maxnum = INT_MAXNUM;
      cstr decimal_maxnum = integral_maxnum + integral_length;
      if (memory_compare(decimal_start, decimal_maxnum, decimal_length) > 0)
        return fail("number overflow");
    }
  }

  /* If the exponent is greater than the maximum representable, it's another overflow. */
  if (unlikely(exponent_length > DEC_EXP_MAXCHARS || exponent > DEC_EXP_MAX))
    return fail("exponent overflow");

#ifdef PARSE_NUMBER__INTEGER
  /* When parsing integers, we have to check that adding the zeros of the exponent
    does not overflow the number. For example, on a 32-bit system, consider the number
    99999 with an exponent of 10^6. The result of the multiplication is 99999000000,
    which is 11 digits long and therefore higher than the 32-bit INT_MAXNUM
    (2147483647). */
  if (unlikely(integral_length + exponent_offset > INT_MAXCHARS)) {
    return fail("number overflow");

  } else if (unlikely(integral_length + exponent_offset == INT_MAXCHARS)) {
    /* When the multiplication of the integer with the exponent results in exactly the
      number of digits of INT_MAXNUM, then we use the char comparison technique --
      as did above -- to determine if it is an overflow. */
    char multiplied_integral[INT_MAXCHARS + 1] = { 0 };
    memory_copy(multiplied_integral, integral_start, integral_length);
    memory_set(multiplied_integral + integral_length, '0', exponent_offset);
    if (memory_compare(multiplied_integral, INT_MAXNUM, INT_MAXCHARS) > 0)
      return fail("number overflow");
  }
#endif

