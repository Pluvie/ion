struct csv_properties;
/**
 * Contains the properties of a CSV file such as separator, encoding, columns, etc. */
struct csv_properties {
  char separator;
  char wrapper;
  u32 columns_count;
  enum charset encoding;
  padding(4);
};
check_sizeof(struct csv_properties, 16);
