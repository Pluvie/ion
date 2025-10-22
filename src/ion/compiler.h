/*
  All supported ⚡️ION⚡️ compilers.
*/

#define GCC     0
#define CLANG   1
#define MSVC    2

#define compiler(name) (COMPILER == name)

#if   defined(__GNUC__)
  #ifndef __clang__
    #define COMPILER  GCC
  #else
    #define COMPILER  CLANG
  #endif

#elif defined(_MSC_VER)
  #define COMPILER  MSVC

#else
  #error "⚡️ION⚡️: Unsupported compiler."
#endif
