void print_failure (
    const cstr message
)
{
  print(FMT_COLOR_RED);
  if (message != nullptr)
    print("%s. ", message);

  if (errno > 0) {
#if platform(WINDOWS)
    char errno_buf[256] = { 0 };
    strerror_s(errno_buf, sizeof(errno_buf), errno);
    print("%"fmt(CSTR)": %"fmt(CSTR)" (%"fmt(CSTR)":%"fmt(CSTR)")",
      failure.message, errno_buf, failure.file, failure.line);
#else
    print("%"fmt(CSTR)": %"fmt(CSTR)" (%"fmt(CSTR)":%"fmt(CSTR)")",
      failure.message, strerror(errno), failure.file, failure.line);
#endif

  } else {
    print("%"fmt(CSTR)" (%"fmt(CSTR)":%"fmt(CSTR)")",
      failure.message, failure.file, failure.line);
  }

  print(FMT_COLOR_NONE);
  print("\n");
}
