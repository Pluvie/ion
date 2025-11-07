
  if (unlikely(number_length > (INT_BITSIZE / 4)))
    /* A single hexadecimal digit can represent up to 4 bits -- 0 > 0000 to F > 1111,
      so if the number length is greater than `INT_BITSIZE / 4` then we have an
      overflow for sure. */
    return fail("number overflow");

  if (unlikely(number_length == (INT_BITSIZE / 4)))
    /* If we happen to have exactly the maximum amount of hexadecimal digits in a
      number -- e.g. on 32-bit systems the number "AB017FF4", then we just have to
      check that the first digit is not "8", as the greatest representable hex number
      in a given architecture is always "7" followed by a number of "F" equal to
      `(INT_BITSIZE / 4) - 1`. */
    if (*integral_start == '8')
      return fail("number overflow");
