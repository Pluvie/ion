/* Defines the `struct iterator` ⚡️ION⚡️ type. */
struct iterator {
  uint position;
  uint index;
#if standard(== C89)
  bool initialized;
#else
  uint gate;
#endif
};
