/**
 * The `erro` type is used to trace a program failure.
 *
 * Example program flow:
 *
 * ```c
 * void failing_function (
 *     void
 * )
 * {
 *   if (read(...) == -1) {
 *     fail("failed to read from xyz");
 *     return;
 *   }
 *   other_stuff();
 * }
 *
 * int32 main (
 *     int32 argc,
 *     char** argv
 * )
 * {
 *   failing_function();
 *   if (unlikely(failure.occurred)) {
 *     error_print();
 *     return EXIT_FAILURE;
 *   }
 *
 *   return EXIT_SUCCESS;
 * }
 *
 * ```
 */
struct error {
  bool occurred;
  padding(4);
  int code;
  int length;
  char message[488];
};
check_sizeof(512, struct error);
