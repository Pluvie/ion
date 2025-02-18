struct sci_notation;
/**
 * Explain the scientific notation. */
struct sci_notation {
  bool negative;
  bool negative_exponent;
  struct string integral;
  struct string fractional;
  struct string exponent;
  padding(8);
};
check_sizeof(struct sci_notation, 64);
