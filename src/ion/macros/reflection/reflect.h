/*
  Reflection entrypoint macro, defining size and type.
*/
#define reflect(size_var, type_var) \
  .size = sizeof(size_var), .type = type_var, \
  .type_name = compile_stringize(size_var)
