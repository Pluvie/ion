struct reflect;
/**
 * Explain what reflection is and how it's useful for object inspection and
 * serialization.
 *
 * ```c
 * struct example {
 *   i32 number;
 *   u32 ages[4];
 *   struct array* values;
 *   struct {
 *     i32 value;
 *   } inner;
 *   struct pointed {
 *     i32 test;
 *     i32 abc;
 *   }* pointed;
 * };
 * 
 * struct reflect example_reflection = {
 *   type(STRUCT, sizeof(struct example)), fields({
 *     { field(struct example, number), type(I32) },
 *     { field(struct example, inner), type(STRUCT), fields({
 *       { field(struct example, inner.value), type(I32) } })
 *     },
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
 * */
struct reflect {
  char* name;
  u32 offset;
  u32 index;
  u32 bounds[2];
  enum types type;
  struct reflect* parent;
  struct vector* child;
  bool initialized;
  bool (*validator)(void*, struct reflect*);
};
check_sizeof(struct reflect, 64);
