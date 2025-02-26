struct string;
/**
 * Explain the string (advantage of not being NULL terminated). */
struct string {
  char* content;
  i32 length;
  padding(4);
};
check_sizeof(struct string, 16);
