/*
  Defines a function specification.
*/
#define spec(function) \
  void spec__ ## function (void)

/*
  Registers a function specification.
*/
#define spec_add(function) \
  added_specs[added_specs_count] = spec__ ## function; \
  added_spec_names[added_specs_count] = #function; \
  added_specs_count++;

/*
  Focuses a function specification.
*/
#define spec_focus(function) \
  focused_specs[focused_specs_count] = spec__ ## function; \
  focused_spec_names[focused_specs_count] = #function; \
  focused_specs_count++;

/*
  Global variable that stores the final result of all specs.
*/
bool specs_passed = true;

/*
  Global variable that stores the original value of stderr.
  All specs by default suppresses any printout.
*/
void* sstream = nullptr;

/*
  Global variable that stores registered specs to be run.
*/
int added_specs_count = 0;
void (*added_specs[8192])(void) = { 0 };
char* added_spec_names[8192] = { 0 };

/*
  Global variable that stores focused specs to be run.
*/
int focused_specs_count = 0;
void (*focused_specs[16])(void) = { 0 };
char* focused_spec_names[16] = { 0 };

/*
  Holds the current indentation level.
*/
int spec_indentation = 0;

/*
  Global variable that enables/disables the printing of spec verifications.
*/
bool spec_print_verification_enabled = false;

/* Runs the registered -- or focused -- specs. */
void specs_run (
    void
)
{
  if (focused_specs[0] == nullptr) {
    sstream = fopen("/dev/null", "w");
    for (int i = 0; i < added_specs_count; i++) {
      spec_indentation = 0;
      fprintf(stderr, PRINT_COLOR_MAGENTA);
      fprintf(stderr, "\n%s", added_spec_names[i]);
      fprintf(stderr, PRINT_COLOR_NONE);
      fflush(stderr);
      spec_indentation = 1;
      added_specs[i]();
    }
  } else {
    sstream = stderr;
    for (int i = 0; i < focused_specs_count; i++) {
      spec_indentation = 0;
      fprintf(stderr, PRINT_COLOR_MAGENTA);
      fprintf(stderr, "\n%s", focused_spec_names[i]);
      fprintf(stderr, PRINT_COLOR_NONE);
      fflush(stderr);
      focused_specs[i]();
    }
  }

  if (specs_passed) {
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_GREEN);
    if (focused_specs[0] == nullptr)
      fprintf(stderr, "Completed %li specs.\n", added_specs_count);
    else
      fprintf(stderr, "Completed %li focused spec(s).\n", focused_specs_count);
    fprintf(stderr, "All specs passed successfully.");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_NONE);
  } else {
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_RED);
    fprintf(stderr, "Some specs did not pass. Check for errors above.");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_NONE);
  }

  fclose(stderr);
  if (focused_specs[0] == nullptr)
    fclose(sstream);
}
