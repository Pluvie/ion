struct http_header;
struct http_header {
  struct string name;
  struct string value;
};
check_sizeof(struct http_header, 32);
