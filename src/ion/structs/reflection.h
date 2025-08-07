/**
 * NOTE(Pluvie): this struct definition is a placeholder, since it is not possible to
 * define the `list<struct reflection>` type here without incurring in circular
 * application of `sizeof`.
 *
 * This struct is the inflected name of a `list<struct reflection>` pointer,
 * effectively anticipating what shall be the final name after the inclusion of the
 * file `src/ion/containers.h`, where all prebuilt data structures are defined. */
struct list_struct_reflection;


struct reflection {
  enum types type;
  string name;
  string type_name;
  int offset;
  int index;
  int size;
  struct {
    int min;
    int max;
  } size_limits;
  struct reflection* parent;
  union {
    /* See the note above. */
    struct list_struct_reflection* fields;
    struct reflection* element;
  };
  bool (*validator)(void*, struct reflection*);
  int (*container_adder)(void*, void*);
  void* (*container_creator)(int, memory*, void*);
  void* support_data;
};
check_sizeof(128, struct reflection);
