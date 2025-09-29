/*
  Used to get a base object with the given type. Useful to calculate offsets or types
  of tagless structs members.
  
  Example:
  
  ```c
  struct example {
    u64 value;
    struct {
      i64 value;
    } inner;
  };
  ```
  
  In the above example, using:
  
  ```c
  o(struct example)->inner
  ```
  
  returns a reference to the inner member of the struct.
*/
#define o(struct_type) \
  ((struct_type*) 0)
