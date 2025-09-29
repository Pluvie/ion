/*
  Defines the fields of a struct reflection.
*/
#define fields(...) \
  .fields = (struct reflection []) { __VA_ARGS__  { 0 } }
