/**
 * NOTE(Pluvie): this struct definition is a placeholder, since it is not possible to
 * define the `list<struct reflection>` here without incurring in circular type
 * application of `sizeof`.
 *
 * The full type shall be defined at the end of `src/ion.h` file, along with all
 * prebuilt inflected data structure types. */
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
  void* support_data;
  padding(16);
};
check_sizeof(128, struct reflection);
