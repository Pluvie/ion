struct result fail (
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

/* Wraps the `fail` function with a macro to conveniently automatically provide file
  name and line number. */
#define fail(message) \
  fail(message, __FILE__, stringize(__LINE__))
