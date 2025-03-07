struct string;
/**
 * Explain the string (advantage of not being NULL terminated). */
struct string {
  char* content;
  u64 length;
};
check_sizeof(struct string, 16);
