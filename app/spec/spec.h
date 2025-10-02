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

/*
  Runs the registered -- or focused -- specs.
*/
void specs_run (
    void
);
