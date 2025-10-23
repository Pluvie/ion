/*
  A string builder.
*/
struct str_builder {
  unsigned int capacity;
  void* memory;
  str result;
};
