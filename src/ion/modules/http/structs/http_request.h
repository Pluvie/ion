struct http_request;
struct http_request {
  enum http_method method;
  enum http_version version;
  struct string uri;
  padding(8);
};
check_sizeof(struct http_request, 32);
