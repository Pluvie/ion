/* Holds the current indentation level. */
int spec_indentation = 0;

/* Defines the spec commands. */
enum spec_commands {
  SPEC__NONE,
  SPEC__ARGUMENT,
  SPEC__PRECONDITION,
  SPEC__WHEN,
  SPEC__WHEN_OR,
  SPEC__APPLY,
  SPEC__MUST,
  SPEC__VERIFY,
  SPEC__SUCCESS,
};

/* Tracks the original stderr stream to allow printing. */
struct stream original_stderr;

/* Global variable that stores registered specs to be run. */
int registered_specs_count = 0;
void (*registered_specs[8192])(void) = { 0 };
char* registered_spec_names[8192] = { 0 };

/* Global variable that stores focused specs to be run. */
int focused_specs_count = 0;
void (*focused_specs[16])(void) = { 0 };
char* focused_spec_names[16] = { 0 };

/* Global variable that enables/disables the printing of spec verifications. */
bool spec_print_verification_enabled = false;

/* Global variable that stores the final result of all specs. */
bool specs_passed = true;

/* Global variable that allows automatic allocation and deallocation in specs. */
memory* spec_allocator;

/* Defines a function specification. */
#define spec(function) \
  void spec__ ## function (void)

/* Registers a function specification. */
#define spec_add(function) \
  registered_specs[registered_specs_count] = spec__ ## function; \
  registered_spec_names[registered_specs_count] = #function; \
  registered_specs_count++;

/* Focuses a function specification. */
#define spec_focus(function) \
  focused_specs[focused_specs_count] = spec__ ## function; \
  focused_spec_names[focused_specs_count] = #function; \
  focused_specs_count++;

/* Defines a function specification argument. */
#define argument(...) \
  __VA_OPT__(__VA_ARGS__;)

/* Defines a function specification precondition. */
#define precondition(cond) \
  spec_print("given " cond);

/* Applies a function specification precondition. */
#define apply(precond, ...) \
  precond __VA_OPT__(; __VA_ARGS__);

/* Defines a function specification codepath. */
#define when(cond) \
  spec_print("when " cond); \
  spec_indentation++;

/* Defines a function specification condition that must be verified. */
#define must(cond) \
  spec_print("must " cond " "); \
  spec_print_verification_enabled = true;

/* Verifies a condition. */
#define verify(cond) \
  if (!(cond)) { spec_failed(#cond, __FILE__, __LINE__ ); } else { spec_verified(); }

/* Checks that the failure has the specified message. */
#define failure_is(msg) \
  (cmp<string>(failure.message, s(msg)) == 0)

/* Defines a function specification codepath success. */
#define success() \
  failure_recover(); \
  spec_print_verification_enabled = false;

/* Ends a specification codepath. */
#define end() \
  spec_indentation--;

/* Prints a spec text with indentation. */
void spec_print (
    const char* text
)
{
  stream_print(&original_stderr, "\n");

  for (int i = 0; i < spec_indentation; i++)
    stream_print(&original_stderr, "  ");
    
  stream_print(&original_stderr, "%s", text);
}

/* Prints a failed spec condition. */
void spec_failed (
    const char* text,
    const char* file,
    int line
)
{
  specs_passed = false;
  stream_print(&original_stderr, PRINT_COLOR_RED);
  stream_print(&original_stderr, "█");
  stream_print(&original_stderr, PRINT_COLOR_NONE);
  stream_print(&original_stderr, "\n");
  for (int i = 0; i < spec_indentation; i++)
    stream_print(&original_stderr, "  ");
  stream_print(&original_stderr, PRINT_COLOR_RED);
  stream_print(&original_stderr, "%s (%s:%li) ", text, file, line);
  stream_print(&original_stderr, PRINT_COLOR_NONE);
}

/* Prints a verified spec condition. */
void spec_verified (
    void
)
{
  if (spec_print_verification_enabled) {
    stream_print(&original_stderr, PRINT_COLOR_GREEN);
    stream_print(&original_stderr, "█");
    stream_print(&original_stderr, PRINT_COLOR_NONE);
  }
}

/* Runs the registered -- or focused -- specs. */
void specs_run (
    void
)
{
  stream_init_defaults();
  spec_allocator = alloc_zero(sizeof(memory));

  if (focused_specs[0] == NULL) {
    original_stderr = stream_duplicate(&__stderr);
    stream_suppress(&__stderr);
  } else {
    original_stderr = stream_duplicate(&__stderr);
  }

  if (focused_specs[0] == NULL) {
    for (int i = 0; i < registered_specs_count; i++) {
      spec_indentation = 0;
      stream_print(&original_stderr, PRINT_COLOR_MAGENTA);
      stream_print(&original_stderr, "\n%s", registered_spec_names[i]);
      stream_print(&original_stderr, PRINT_COLOR_NONE);
      stream_flush(&original_stderr);
      spec_indentation = 1;
      registered_specs[i]();
      memory_release(spec_allocator);
    }
  } else {
    for (int i = 0; i < focused_specs_count; i++) {
      spec_indentation = 0;
      stream_print(&original_stderr, PRINT_COLOR_MAGENTA);
      stream_print(&original_stderr, "\n%s", focused_spec_names[i]);
      stream_print(&original_stderr, PRINT_COLOR_NONE);
      stream_flush(&original_stderr);
      focused_specs[i]();
      memory_release(spec_allocator);
    }
  }

  if (specs_passed) {
    stream_print(&original_stderr, "\n");
    stream_print(&original_stderr, "\n");
    stream_print(&original_stderr, PRINT_COLOR_GREEN);
    if (focused_specs[0] == NULL)
      stream_print(&original_stderr, "Completed %li specs.\n", registered_specs_count);
    else
      stream_print(&original_stderr, "Completed %li focused spec(s).\n", focused_specs_count);
    stream_print(&original_stderr, "All specs passed successfully.");
    stream_print(&original_stderr, "\n");
    stream_print(&original_stderr, PRINT_COLOR_NONE);
  } else {
    stream_print(&original_stderr, "\n");
    stream_print(&original_stderr, "\n");
    stream_print(&original_stderr, PRINT_COLOR_RED);
    stream_print(&original_stderr, "Some specs did not pass. Check for errors above.");
    stream_print(&original_stderr, "\n");
    stream_print(&original_stderr, PRINT_COLOR_NONE);
  }

  stream_close(&original_stderr);
  stream_close(&__stderr);
  alloc_release(spec_allocator);
}
