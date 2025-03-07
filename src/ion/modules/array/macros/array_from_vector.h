/**
 * Creates an array from a vector. */
#define array_from_vector(vec)      \
  (struct array) {                  \
    .typesize = (vec)->typesize,    \
    .data = (vec)->data,            \
    .length = (vec)->length }
