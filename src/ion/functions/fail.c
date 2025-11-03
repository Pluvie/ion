enum result fail (
    const cstr message,
    const cstr file,
    const cstr line
)
{
  failure.message = message;
  failure.file = file;
  failure.line = line;
  return Failure;
}

/* Wraps the `fail` function with a macro to conveniently automatically provide file
  name and line number. */
#define fail(message) \
  fail(message, __FILE__, stringize(__LINE__))
