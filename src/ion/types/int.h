/*
  Defines the `int` and `int0` ⚡️ION⚡️ types.

  `int` is always the widest possible integer that can be operated with a single
  hardware instruction on the target architecture. For example, on Linux systems, it is
  64 bit wide. This type can be seen as a signed replacement to `size_t`.

  `int0` is the native integer type as implemented on the target architecture. For
  example, on Linux systems, it is 32 bit wide. This serves as a fallback type when the
  original int type is required. For example, using ⚡️ION⚡️, the `main` function must
  return an `int0` because the C standard defines that this function must return the
  native int type. On a Linux system, if we would have used the `int` type as return
  type for the `main` function, the program would not compile, because `int` is 64 bit
  and `int0` is 32 bit. On a Windows32 system, using `int` as return type for the `main`
  function, would instead compile, because `int` and `int0` are both 32 bit wide.


  The main reason why ⚡️ION⚡️ wants to use and specify a unique `int` type is for
  code clarity. We recognize the great achievements made by the `size_t` type, but
  we also feel like it is time to move on from the inevitable opacity and confusion
  that was introduced with this type.

  By having an unique `int` type, which represent the widest possible integer on the
  target architecture, we can offer the
  [same portability benefits](https://pvs-studio.com/en/blog/posts/cpp/a0050/) of the
  `size_t` pointer, with the increased code clarity and readability.

  Why is ⚡️ION⚡️ `int` type not the widest possible integer, in general, on the target
  architecture? Because [there are cases](https://stackoverflow.com/a/4295225) where in
  some machines, such as Windows32 or the PDP-11, using the widest possible integer
  leads to performance degradation, due to hardware using multiple instructions to
  handle it. For example, Windows32 has support for 64 bit wide integers, rendering it
  effectively the widest possible integer on its architecture, but it must use multiple
  hardware instructions to manage two 32 bit registers that compose the 64 bit integer.

  This is why ⚡️ION⚡️ defines `int` as:
  > the widest possible integer that can be operated with a single hardware instruction
    on the target architecture.
*/

#if INT_BIT_WIDTH != 64 && INT_BIT_WIDTH != 32
#error "⚡️ION⚡️ supports only 64 or 32 bit wide integers."
#endif

/*
  `native_int_t` must be defined in each platform header file. It must be always
  defined as `typedef int native_int_t;` in order to capture the native int type.
*/
#ifdef  int0
#undef  int0
#endif

#define int0  native_int_t

/*
  `widest_int_t` must be defined in each platform header file. It must not be defined
  as a typedef, but rather as a constant, in order to allow it to be use with the
  `unsigned` qualifier.
*/
#ifdef  int
#undef  int
#endif

#define int   widest_int_t
