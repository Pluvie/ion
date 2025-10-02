/*
  This macro is used to branch on whether variadic args have been passed.
*/
#define if_va_args(...) \
  (__VA_OPT__(true ||) false)
