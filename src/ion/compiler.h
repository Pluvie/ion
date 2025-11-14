/* ⚡️ION⚡️ compilers mapping.

  The `compiler` macro can be used as a preprocessor directive to check if a given
  compiler is being used. This can help to safely introduce compiler specific builtins
  or other compiler specific features. An example can be found in the
  `src/ion/functions/bit_count_leading_zeros.c` file. */

#define GCC     0
#define CLANG   1
#define MSVC    2

#define compiler(name) (COMPILER == name)

#if   defined(__clang__)
#define COMPILER  CLANG

#elif defined(__GNUC__)
#define COMPILER  GCC

#elif defined(_MSC_VER)
#define COMPILER  MSVC

#else
#error "ION: Unsupported compiler -- contributions to support it are most welcome."
#endif
