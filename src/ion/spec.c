/* Global variable that stores the original value of stderr.
  All specs by default suppresses any printout. */
void* sstream = nullptr;

/* Global variable that stores the final result of all specs. */
bool specs_passed = true;

/* Holds the current indentation level. */
int spec_indentation = 0;

/* Global variable that enables/disables the printing of spec verifications. */
bool spec_print_verification_enabled = false;

/* Global variable that helps allocating temporary data for specs. */
struct allocator* spec_allocator;

/* Global variable that stores registered specs to be run. */
int added_specs_count = 0;
void (*added_specs[8192])(void) = { 0 };
cstr added_spec_names[8192] = { 0 };

/* Global variable that stores focused specs to be run. */
int focused_specs_count = 0;
void (*focused_specs[16])(void) = { 0 };
cstr focused_spec_names[16] = { 0 };

/* Prints a spec text with indentation. */
void spec_print (
    const cstr text
)
{
  fprintf(stderr, "\n");

  { int i; for (i = 0; i < spec_indentation; i++)
    fprintf(stderr, "  "); }
    
  fprintf(stderr, "%s", text);
}

/* Prints a failed spec condition. */
void spec_failed (
    const cstr text,
    const cstr file,
    int line
)
{
  specs_passed = false;
  fprintf(stderr, FMT_COLOR_RED);
  fprintf(stderr, "!");
  fprintf(stderr, FMT_COLOR_NONE);
  fprintf(stderr, "\n");
  { int i; for (i = 0; i < spec_indentation; i++)
    fprintf(stderr, "  "); }
  fprintf(stderr, FMT_COLOR_RED);
  fprintf(stderr, "%s (%s:%i) ", text, file, (int_t) line);
  fprintf(stderr, FMT_COLOR_NONE);
}

/* Prints a verified spec condition. */
void spec_verified (
    void
)
{
  if (spec_print_verification_enabled) {
    fprintf(stderr, FMT_COLOR_GREEN);
    fprintf(stderr, ".");
    fprintf(stderr, FMT_COLOR_NONE);
  }
}

/* Runs the registered specs. If there is one or more focused specs, runs only those. */
void specs_run (
    void
)
{
  int i;

  spec_allocator = memory_acquire(sizeof(*spec_allocator));
  *spec_allocator = allocator_init(0);

  if (focused_specs[0] == nullptr) {
    sstream = fopen("/dev/null", "w");
    for (i = 0; i < added_specs_count; i++) {
      spec_indentation = 0;
      fprintf(stderr, FMT_COLOR_MAGENTA);
      fprintf(stderr, "\n%s", added_spec_names[i]);
      fprintf(stderr, FMT_COLOR_NONE);
      fflush(stderr);
      spec_indentation = 1;
      added_specs[i]();
      allocator_release(spec_allocator);
      /*memory_set(&failure, 0, sizeof(failure));*/
    }
  } else {
    sstream = stderr;
    for (i = 0; i < focused_specs_count; i++) {
      spec_indentation = 0;
      fprintf(stderr, FMT_COLOR_MAGENTA);
      fprintf(stderr, "\n%s", focused_spec_names[i]);
      fprintf(stderr, FMT_COLOR_NONE);
      fflush(stderr);
      focused_specs[i]();
      allocator_release(spec_allocator);
      /*memory_set(&failure, 0, sizeof(failure));*/
    }
  }

  if (specs_passed) {
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, FMT_COLOR_GREEN);
    if (focused_specs[0] == nullptr)
      fprintf(stderr, "Completed %i specs.\n", (int_t) added_specs_count);
    else
      fprintf(stderr, "Completed %i focused spec(s).\n", (int_t) focused_specs_count);
    fprintf(stderr, "All specs passed successfully.");
    fprintf(stderr, "\n");
    fprintf(stderr, FMT_COLOR_NONE);
  } else {
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, FMT_COLOR_RED);
    fprintf(stderr, "Some specs did not pass. Check for errors above.");
    fprintf(stderr, "\n");
    fprintf(stderr, FMT_COLOR_NONE);
  }

  allocator_release(spec_allocator);
  memory_release(spec_allocator);

  fclose(stderr);
  if (focused_specs[0] == nullptr)
    fclose(sstream);
}
