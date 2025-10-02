/*
  Prints a fake compile time error which shows the bytesize of a *type*.
  
  The error is totally fake, it just helps to know the exact bytesize of a type,
  after the compiler has done potential paddings.
*/
#define print_sizeof(type) \
  static char __fake_var[sizeof(type)] = { __fake_error(&__fake_var) };

#ifdef ION_EXEC
char __fake_error(int);
#endif
