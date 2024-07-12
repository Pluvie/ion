struct reflect;
/**
 * Explain what reflection is and how it's useful for serialization.
 *
 * Limitations:
 *
 * - unions are not supported.
 * - structs **must** have a tag or be typedef'd: this is because the #field macro
 *   needs an identifiable struct type to calculate the field offset. Example:
 *
 * ```c
 * struct example {
 *   i32 a;
 *   struct {   // This struct won't work, because it's tagless: therefore it's not 
 *     i32 b;   // possible to calculate the offsets of its fields at compile time,
 *     i32 c;   // because the `offsetof` macro requires an identifiable tag.
 *   } d;
 * };
 * ```
 *
 * */
struct reflect {
  u64 offset;
  u64 bounds[2];
  u64 index;
  char* name;
  enum types type;
  struct reflect* parent;
  struct reflect* child;
};
check_sizeof(struct reflect, 64);
