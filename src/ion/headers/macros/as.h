/**
 * Retrieves the value of the given `void*` *pointer* casted to the given *type*. */
#define as(type, pointer) \
  (pointer != NULL ? (*(type*) (pointer)) : (type) { 0 })
