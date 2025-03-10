struct range;
/**
 * A `struct range` represents a numerical distance between two values. */
struct range {
  i64 min;
  i64 max;
  i64 at;
  padding(8);
};
check_sizeof(struct range, 32);
