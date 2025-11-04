struct result fail_internal (
    bool with_errno,
    const cstr message,
    const cstr file,
    const cstr line
)
{
  struct result failure = { false, true, 0 };
  failure.message = message;
  failure.file = file;
  failure.line = line;
  return failure;
}

/* Wraps the `fail_internal` function with a macro to conveniently automatically provide
  file name and line number. */
#define fail(message) \
  fail_internal(false, message, __FILE__, stringize(__LINE__))

/* Wraps the `fail_internal` function with a macro to conveniently automatically provide
  file name and line number and also an indicator that the `errno` global variable
  contains useful information about the failure. */
#define fail_with_errno(message) \
  fail_internal(true, message, __FILE__, stringize(__LINE__))
