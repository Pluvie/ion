/*
  Defines a field of a struct reflection.
*/
#define field(struct_type, enum_type, name_var, ...)                    \
  .name = #name_var,                                                    \
  .type = enum_type,                                                    \
  .offset = offsetof(struct_type, __VA_OPT__(__VA_ARGS__.)name_var)     \
    __VA_OPT__(- offsetof(struct_type, __VA_ARGS__)),                   \
  .size = sizeof(((struct_type*)0)->__VA_OPT__(__VA_ARGS__.)name_var)
