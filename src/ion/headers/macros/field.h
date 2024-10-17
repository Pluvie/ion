/**
 * Used to define a struct field in a protocol schema. */
#define field(struct_name, field_name)  \
  .offset = offsetof(struct_name, field_name), .name = #field_name
