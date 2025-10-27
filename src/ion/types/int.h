/* Defines the `int_t` and `uint_t` types.

  `int_t` is the native integer type as implemented on the target architecture. For
  example, on Linux systems, it is 32 bit wide. This serves as a fallback type when the
  original int type is required. For example, using ⚡️ION⚡️, the `main` function must
  return an `int_t` because the C standard defines that this function must return the
  native int type. On a 64-bit Linux system, if we used the `int` type as return type
  for the `main` function, the program would not compile, because `int` is 64 bit and
  `int_t` is 32 bit. On a 32-bit Windows system, using `int` as return type for the
  `main` function, would instead compile, because `int` and `int_t` are both 32 bit
  wide. */

typedef int             int_t;
typedef unsigned int    uint_t;

/* Defines the `int` integer ⚡️ION⚡️ types.

  `int` is always the widest possible integer that can be operated with a single
  hardware instruction on the target architecture. For example, on a 64-bit Linux
  system, it is 64 bit wide. In this case, this type can be seen as a replacement to
  `int64_t`.

  The main reason why ⚡️ION⚡️ wants to use and specify a unique `int` type is for
  code clarity. We recognize the great achievements made by the `size_t` type, but
  we also feel like it is time to move on from the inevitable opacity and confusion
  that was introduced with this type.

  By having an unique `int` type, which represent the widest possible integer on the
  target architecture, we can offer the
  [same portability benefits](https://pvs-studio.com/en/blog/posts/cpp/a0050/) of the
  `size_t` pointer, with the increased code clarity and readability.

  Why is ⚡️ION⚡️ `int` type not the widest possible integer, in general, on the target
  architecture? Because [some combinations of platform and architecture](
  https://stackoverflow.com/a/4295225), such as 32-bit Windows, have support for 64-bit
  wide integers, but they require multiple hardware instructions to operate. Therefore,
  this leads to unoptimized code and performance degradation, and we want to avoid that.

  This is why ⚡️ION⚡️ defines `int` as:
  > the widest possible integer that can be operated with a single hardware instruction
    on the target architecture. */

#ifdef int
#undef int
#endif

#if compiler(CLANG) /* Ignores the "keyword is hidden warning" emitted only by Clang. */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif
#define int   widest_int_t
#if compiler(CLANG)
#pragma clang diagnostic pop   
#endif

#ifdef uint
#undef uint
#endif

#define uint  widest_uint_t
