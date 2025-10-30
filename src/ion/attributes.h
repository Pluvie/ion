/* Provides a common definition for function attributes. */


/* `no_discard` attribute: the function return value must always be checked. */
#if standard(>= C23)
#define Attribute__No_Discard \
  [[nodiscard]]
#else

#if compiler(GCC) || compiler(CLANG)
#define Attribute__No_Discard \
  __attribute__((warn_unused_result))

#elif compiler(MSVC)
#define Attribute__No_Discard \
  _Check_return_

#else
#define Attribute__No_Discard
#endif
#endif

/* `format` attribute: the function behaves like a printf-style, so, if the compiler
  has support for it, it can check the arguments at compile time. */
#if compiler(GCC) || compiler(CLANG)
#define Attribute__Format(type, start, first) \
  __attribute__((format (type, start, first)))

#else
#define Attribute__Format(type, start, first)
#endif
