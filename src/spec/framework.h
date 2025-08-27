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
  fprintf(original_stderr, "\n");

  for (int i = 0; i < spec_indentation; i++)
    fprintf(original_stderr, "  ");
    
  fprintf(original_stderr, "%s", text);
}

/* Prints a failed spec condition. */
void spec_failed (
    const char* text,
    const char* file,
    int line
)
{
  specs_passed = false;
  fprintf(original_stderr, PRINT_COLOR_RED);
  fprintf(original_stderr, "█");
  fprintf(original_stderr, PRINT_COLOR_NONE);
  fprintf(original_stderr, "\n");
  for (int i = 0; i < spec_indentation; i++)
    fprintf(original_stderr, "  ");
  fprintf(original_stderr, PRINT_COLOR_RED);
  fprintf(original_stderr, "%s (%s:%li) ", text, file, line);
  fprintf(original_stderr, PRINT_COLOR_NONE);
}

/* Prints a verified spec condition. */
void spec_verified (
    void
)
{
  if (spec_print_verification_enabled) {
    fprintf(original_stderr, PRINT_COLOR_GREEN);
    fprintf(original_stderr, "█");
    fprintf(original_stderr, PRINT_COLOR_NONE);
  }
}

/* Runs the registered -- or focused -- specs. */
void specs_run (
    void
)
{
  spec_allocator = alloc_zero(sizeof(memory));

  if (focused_specs[0] == NULL) {
    original_stderr = fdopen(STDERR_FILENO, "w");
    stderr = fopen("/dev/null", "w");
  } else {
    original_stderr = fdopen(STDERR_FILENO, "w");
  }

  if (focused_specs[0] == NULL) {
    for (int i = 0; i < registered_specs_count; i++) {
      spec_indentation = 0;
      fprintf(original_stderr, PRINT_COLOR_MAGENTA);
      fprintf(original_stderr, "\n%s", registered_spec_names[i]);
      fprintf(original_stderr, PRINT_COLOR_NONE);
      fflush(original_stderr);
      spec_indentation = 1;
      registered_specs[i]();
      memory_release(spec_allocator);
    }
  } else {
    for (int i = 0; i < focused_specs_count; i++) {
      spec_indentation = 0;
      fprintf(original_stderr, PRINT_COLOR_MAGENTA);
      fprintf(original_stderr, "\n%s", focused_spec_names[i]);
      fprintf(original_stderr, PRINT_COLOR_NONE);
      fflush(original_stderr);
      focused_specs[i]();
      memory_release(spec_allocator);
    }
  }

  if (specs_passed) {
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_GREEN);
    if (focused_specs[0] == NULL)
      fprintf(original_stderr, "Completed %li specs.\n", registered_specs_count);
    else
      fprintf(original_stderr, "Completed %li focused spec(s).\n", focused_specs_count);
    fprintf(original_stderr, "All specs passed successfully.");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_NONE);
  } else {
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_RED);
    fprintf(original_stderr, "Some specs did not pass. Check for errors above.");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_NONE);
  }

  fclose(original_stderr);
  fclose(stderr);
  free(spec_allocator);
}
