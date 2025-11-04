struct result print_failure (
    const cstr description,
    struct result* failure
)
{
  print(FMT_COLOR_RED);
  if (description != nullptr)
    print("%"fmt(CSTR)": ", description);

  print("%"fmt(CSTR)".", failure->message);

  if (failure->with_errno) {
#if platform(WINDOWS)
    char errno_buf[256] = { 0 };
    strerror_s(errno_buf, sizeof(errno_buf), errno);
    print(" %"fmt(CSTR)" ", errno_buf);
#else
    print(" %"fmt(CSTR)" ", strerror(errno));
#endif
  }

  print("(%"fmt(CSTR)":%"fmt(CSTR)")", failure->file, failure->line);
  print(FMT_COLOR_NONE);
  print("\n");

  return *failure;
}
