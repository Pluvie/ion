/*
  Format specifier using generic selector to use with printf-like functions.
*/
struct print_arg {
  const char type;
  const void* value;
};

#define f(v)                                                \
  _Generic((v),                                             \
    bool:               &(struct print_arg) { 'b', &(v) },  \
    char:               &(struct print_arg) { 'c', &(v) },  \
    unsigned char:      &(struct print_arg) { 'k', &(v) },  \
    short:              &(struct print_arg) { 's', &(v) },  \
    unsigned short:     &(struct print_arg) { 'h', &(v) },  \
    int0:               &(struct print_arg) { 'i', &(v) },  \
    unsigned:           &(struct print_arg) { 'u', &(v) },  \
    long:               &(struct print_arg) { 'l', &(v) },  \
    unsigned long:      &(struct print_arg) { 'v', &(v) },  \
    long long:          &(struct print_arg) { 'w', &(v) },  \
    unsigned long long: &(struct print_arg) { 'y', &(v) },  \
    char*:              &(struct print_arg) { 's', &(v) },  \
    void*:              &(struct print_arg) { 'p', &(v) }   \
  )
