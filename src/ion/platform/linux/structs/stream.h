struct stream {
  void* pointer;
  const char* mode;
};
check_sizeof(16, struct stream);
