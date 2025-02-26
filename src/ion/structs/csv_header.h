struct csv_header;
/**
 * Contains the header of a CSV file and its data. */
struct csv_header {
  char* name;
  u64 index;
  struct object* target;
  padding(8);
};
check_sizeof(struct csv_header, 32);
