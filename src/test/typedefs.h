/**
 * Defines an example user defined type. Used for some tests. */
typedef struct {
  u64 id;
  u32 age;
  padding(4);
  string name;
  string email;
} User;
