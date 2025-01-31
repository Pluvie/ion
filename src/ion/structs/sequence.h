struct sequence;
/**
 * A `struct sequence` is a fixed and ordered list of values.
 *
 * These values are stored in a `struct vector`. */
struct sequence {
  struct vector* values;
  u64 current;
  u64 index;
  padding(8);
};
check_sizeof(struct sequence, 32);
