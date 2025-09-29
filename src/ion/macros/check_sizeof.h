/*
  Checks the bytesize of a *type* at compile time.
  
  Example:
  
  ```c
  check_sizeof(1024, struct example);
  ```
  
  If the bytesize of the given type does not match the given *size*, throws a
  compile error.
*/
#define check_sizeof(size, ...) \
  compile_time_check(sizeof(__VA_ARGS__) == size, \
    "must have size of " #size " bytes");
