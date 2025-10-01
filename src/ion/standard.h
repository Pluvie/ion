#ifndef __STDC_VERSION__
#error "⚡️ION⚡️ requires at least C99 standard."
#else
  #define C99 199901L
  #define C11 201112L
  #define C17 201710L
  #define C23 202000L

  #define standard(...) \
    __STDC_VERSION__ __VA_ARGS__
#endif
