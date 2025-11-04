struct result {
  bool success;
  bool failure;
  bool with_errno;
  const cstr message;
  const cstr file;
  const cstr line;
};
