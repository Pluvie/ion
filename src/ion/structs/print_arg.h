struct print_arg {
  const char flag;
  int (*functor)(void*, int, const void*);
  const void* value;
};
