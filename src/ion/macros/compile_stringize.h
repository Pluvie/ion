/**
 * Converts the argument to a literal string. */
#define compile_stringize(arg) \
  compile_stringize_indirect(arg)




/**
 * Layer of macro indirection to make the #compile_stringize macro work. */
#define compile_stringize_indirect(arg) \
  #arg
