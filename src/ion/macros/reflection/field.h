/*
  Defines a field of a reflection of a struct type.
*/
#define field(struct_type, enum_type, name_var, ...)  \
  (struct reflection) {                               \
    .name = string(#name_var),                        \
    .type = enum_type,                                \
    .offset = offsetof(struct_type, name_var),        \
    .size = sizeof(((struct_type*)0)->name_var),      \
    __VA_ARGS__                                       \
  }
