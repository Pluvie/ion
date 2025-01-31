/**
 * Check the bytesize of a *type* at compile time.
 *
 * Example:
 *
 * ```c
 * check_sizeof(ExampleType, 1024);
 * ```
 *
 * If the bytesize of the given *type* does not match the given *bytesize*,
 * throws a compile error. */
#define check_sizeof(type, bytesize) \
  compile_time_check(sizeof(type) == bytesize, \
    #type " must have size of " #bytesize " bytes");
