/*
  Defines the `int` integer ⚡️ION⚡️ types.

  `int` is always the widest possible integer that can be operated with a single
  hardware instruction on the target architecture. For example, on a 64-bit Linux
  system, it is 64 bit wide. In this case, this type can be seen as a replacement to
  `int64_t`.

  Then, defines the `int0` and `uint0` types.

  `int0` is the native integer type as implemented on the target architecture. For
  example, on Linux systems, it is 32 bit wide. This serves as a fallback type when the
  original int type is required. For example, using ⚡️ION⚡️, the `main` function must
  return an `int0` because the C standard defines that this function must return the
  native int type. On a 64-bit Linux system, if we used the `int` type as return type
  for the `main` function, the program would not compile, because `int` is 64 bit and
  `int0` is 32 bit. On a 32-bit Windows system, using `int` as return type for the
  `main` function, would instead compile, because `int` and `int0` are both 32 bit wide.


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
    on the target architecture.
*/

/*
  `native_int_t` must be defined as `typedef int native_int_t;` in order to capture
  the native int type.
*/
typedef int           native_int_t;
typedef unsigned int  native_uint_t;

/*
  Exposes the `int0` and `uint0` type for interoperability with the native int type.
*/
#ifdef  int0
#undef  int0
#endif

#define int0  native_int_t

#ifdef  uint0
#undef  uint0
#endif

#define uint0 native_uint_t

/*
  `widest_int_t` must be defined in each platform header file. It must not be defined
  as a typedef, but rather as a constant, in order to allow it to be use with the
  `unsigned` qualifier.
*/
#ifdef  int
#undef  int
#endif

#define int   widest_int_t

/*
  Defines the INT_MAXCHARS constant, which is directly derived from the platform
  dependent INT_MAXNUM constant. On 32-bit systems, the INT_MAXCHARS constant is equal
  to 10 -- because 2147483647 is the greatest integer (2^31 - 1), which is 10 digits
  long. On 64-bit systems, the INT_MAXCHARS constant is equal to 19 -- because
  9223372036854775807 is the greatest integer (2^63 - 1).
*/
#define INT_MAXCHARS  (sizeof(INT_MAXNUM)-1)
