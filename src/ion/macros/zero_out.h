/**
 * Zeroes out a memory address with specified length. */
#define zero_out(address, length) \
  byte_set(address, 0, length)
