/**
 * Creates a vector from an array. */
#define vector_from_array(ary)      \
  (struct vector) {                 \
    .typesize = (ary)->typesize,    \
    .data = (ary)->data,            \
    .length = (ary)->length }
