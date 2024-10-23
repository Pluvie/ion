struct range;
/**
 * A `struct range` represents a numerical distance between two values. */
struct range {
  u64 min;
  u64 max;
  u64 at;
  padding(8);
};
check_sizeof(struct range, 32);
