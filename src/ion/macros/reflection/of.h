/*
  Used to define a nested type in a reflection.
  Usually seen in presence of pointers and arrays.
*/
#define of(...) \
  .element = &(struct reflection) { __VA_ARGS__ }
