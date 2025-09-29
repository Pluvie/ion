#ifndef __STDC_VERSION__
#error "⚡️ION⚡️ requires at least C11 standard."
#else
  #define C11 201112L
  #define C17 201710L
  #define C23 202000L

  #define standard(...) \
    __STDC_VERSION__ __VA_ARGS__
#endif

#if standard(< C11)
  #error "⚡️ION⚡️ requires at least C11 standard."
#endif
