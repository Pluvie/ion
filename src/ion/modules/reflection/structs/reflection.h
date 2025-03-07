struct reflection;
/**
 * Explain what reflection is and how it's useful for object inspection and
 * serialization.
 *
 * ```c
 * struct example {
 *   i32 number;
 *   u32 ages[4];
 *   struct array* values;
 *   struct pointed {
 *     i32 test;
 *     i32 abc;
 *   }* pointed;
 * };
 * 
 * struct reflection example_reflection = {
 *   type(STRUCT, sizeof(struct example)), fields({
 *     { field(struct example, number), type(I32) },
 *     { field(struct example, ages), type(SEQUENCE, 4), of({ type(U32) }) },
 *     { field(struct example, values), type(ARRAY, 1, 3), of({
 *         type(ARRAY), of({ type(BYTE) })
 *       })
 *     },
 *     { field(struct example, pointed), type(POINTER), of({
 *         type(STRUCT), fields({
 *           { field(struct pointed, test), type(I32) },
 *           { field(struct pointed, abc), type(I32) },
 *         })
 *       })
 *     }
 *   })
 * };
 * ```
 *
 * Tagless structs are supported, but their fields must be defined using the parent
 * struct, in order to be able to calculate their offset.
 *
 * Also, when defining a reflection for a tagless struct, its size can be skipped,
 * as it shall be calculated at runtime with the `reflection_initialize` function.
 *
 * When using a tagless struct as root element for a reflection, the macro `field`
 * cannot be used, and the offset of the fields must be provided manually.
 *
 * ```c
 * struct example {
 *   i32 number;
 *   struct {
 *     i32 value_x;
 *     i32 value_y;
 *   } inner;
 * };
 * 
 * struct reflection example_reflection = {
 *   type(STRUCT, sizeof(example)), fields({
 *     { field(struct example, number), type(I32) },
 *     { field(struct example, inner), type(STRUCT), fields({
 *       { field(struct example, inner.value_x), type(I32) } }),
 *       { field(struct example, inner.value_y), type(I32) } }),
 *     },
 *   })
 * };
 * ```
 *
 * */
struct reflection {
  u64 offset;
  u64 index;
  u64 size;
  u64 length;
  enum types type;
  struct string* name;
  union {
    struct vector* fields;
    struct reflection* element;
  };
  void* target;
  struct reflection* parent;
  struct memory* allocator;
  bool (*validator)(void*, struct reflection*);
  struct {
    u64 min;
    u64 max;
  } size_limits;
  padding(24);
};
check_sizeof(struct reflection, 128);
