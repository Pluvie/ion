/* ⚡️ION⚡️ compilers mapping.  */

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
