/*
  Returns the minimum between two values.
*/
#undef  min
#define min(v, u) \
  (v <= u ? v : u)
