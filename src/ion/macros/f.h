/*
  Format specifier using generic selector to use with printf-like functions.
*/

#define f(v)                                                                            \
  _Generic((v),                                                                         \
    bool:               &(struct print_arg) { 0, PRINT_ARG__BOOL,       &(v) },         \
    char:               &(struct print_arg) { 0, PRINT_ARG__CHAR,       &(v) },         \
    unsigned char:      &(struct print_arg) { 0, PRINT_ARG__UCHAR,      &(v) },         \
    short:              &(struct print_arg) { 0, PRINT_ARG__SHORT,      &(v) },         \
    unsigned short:     &(struct print_arg) { 0, PRINT_ARG__USHORT,     &(v) },         \
    int0:               &(struct print_arg) { 0, PRINT_ARG__INT,        &(v) },         \
    unsigned:           &(struct print_arg) { 0, PRINT_ARG__UINT,       &(v) },         \
    long:               &(struct print_arg) { 0, PRINT_ARG__LONG,       &(v) },         \
    unsigned long:      &(struct print_arg) { 0, PRINT_ARG__ULONG,      &(v) },         \
    long long:          &(struct print_arg) { 0, PRINT_ARG__LONGLONG,   &(v) },         \
    unsigned long long: &(struct print_arg) { 0, PRINT_ARG__ULONGLONG,  &(v) },         \
    dec:                &(struct print_arg) { 0, PRINT_ARG__DEC,        &(v) },         \
    char*:              &(struct print_arg) { 0, PRINT_ARG__CHAR_P,     &(v) },         \
    void*:              &(struct print_arg) { 0, PRINT_ARG__VOID_P,     &(v) }          \
  )
