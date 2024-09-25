/**
 * Calls the given *procedure*, and handles the result.
 * The procedure arguments are passed using the variadic argument.
 *
 * Example:
 *
 * ```c
 * proc(example_procedure, { 42 }) {
 *   print("The procedure has returned %i.", result.example);
 * }
 * ```
 *
 * This macro always creates a local variable named `result` which contains the
 * procedure return value.
 *
 * It is mandatory that this macro content remain on one line, otherwise the `lvar`
 * macros will not work. */
#define proc(procedure, ...) \
  u32 lvar(call) = 0; proc_initializer(procedure __VA_OPT__(, __VA_ARGS__)); lvar(call) == 0; lvar(call) = 1)
