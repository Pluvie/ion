/*
  This macro tests the equality of two C strings, nul terminated.
*/
#define cstreq(v1, v2) \
  (strcmp(v1, v2) == 0)
