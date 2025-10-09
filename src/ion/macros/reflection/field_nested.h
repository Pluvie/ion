/*
  Defines a field of a reflection of a nested struct type.
*/
#define field_nested(struct_type, enum_type, name_var, nested_path, ...)  \
  (struct reflection) {                                                   \
    .name = string(#name_var),                                            \
    .type = enum_type,                                                    \
    .offset = offsetof(struct_type, nested_path.name_var) -               \
      offsetof(struct_type, nested_path),                                 \
    .size = sizeof(((struct_type*)0)->nested_path.name_var),              \
    __VA_ARGS__                                                           \
  }
