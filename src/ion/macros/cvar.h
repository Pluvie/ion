/*
  Generates a unique variable name using the global counter number.
*/
#define cvar(name) \
  compile_concat(name, __COUNTER__)
