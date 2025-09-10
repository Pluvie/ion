struct io_direct {
  string* data;
  char* cursor;
  char* end;
};
check_sizeof(24, struct io_direct);
