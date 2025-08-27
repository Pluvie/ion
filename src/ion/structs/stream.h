struct stream {
  void* pointer;
  string name;
  const char* mode;
};
check_sizeof(32, struct stream);
