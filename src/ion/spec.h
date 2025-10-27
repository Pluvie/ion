/* Defines a function specification. */
#define spec(function) \
  void spec__ ## function (void)

/* Registers a function specification. */
#define spec_add(function) \
  added_specs[added_specs_count] = spec__ ## function; \
  added_spec_names[added_specs_count] = #function; \
  added_specs_count++;

/* Focuses a function specification. */
#define spec_focus(function) \
  focused_specs[focused_specs_count] = spec__ ## function; \
  focused_spec_names[focused_specs_count] = #function; \
  focused_specs_count++;

/* Defines a function specification. */
#define spec(function) \
  void spec__ ## function (void)

/* Defines a function specification argument. */
#define argument(arg) \
  arg

/* Defines a function specification return value. */
#define returns(value) \
  value

/* Defines a function specification precondition. */
#define precondition(cond) \
  spec_print("given " cond);

/* Applies a function specification precondition. */
#define apply(cond) \
  cond

/* Defines a function specification codepath. */
#define when(cond) \
  spec_print("when " cond); \
  spec_indentation++; \
  memory_set(&sim, 0, sizeof(sim));

/* Defines a function specification condition that must be verified. */
#define must(cond) \
  spec_print("must " cond " "); \
  spec_print_verification_enabled = true;

/* Verifies a condition.  */
#define verify(cond) \
  if (!(cond)) { spec_failed(#cond, __FILE__, __LINE__ ); } else { spec_verified(); }

/* Defines a function specification codepath success. */
#define success() \
  spec_print_verification_enabled = false;
  /*memory_set(&failure, 0, sizeof(failure));*/

/* Ends a specification codepath. */
#define end() \
  spec_indentation--;

/* Defines a spec dependency. */
#define dependency(func) \
  dependency__ ## func

/* Defines a specced function copy. */
#define specced(func) \
  specced__ ## func

/* Global variable that stores the original value of stderr.
  All specs by default suppresses any printout. */
extern void* sstream;

/* Global variable that stores the final result of all specs. */
extern bool specs_passed;

/* Holds the current indentation level. */
extern int spec_indentation;

/* Global variable that enables/disables the printing of spec verifications. */
extern bool spec_print_verification_enabled;

/* Global variable that helps allocating temporary data for specs. */
extern struct allocator* spec_allocator;

/* Global variable that stores registered specs to be run. */
extern int added_specs_count;
extern void (*added_specs[8192])(void);
extern cstr added_spec_names[8192];

/* Global variable that stores focused specs to be run. */
extern int focused_specs_count;
extern void (*focused_specs[16])(void);
extern cstr focused_spec_names[16];

/* Runs the registered -- or focused -- specs. */
void specs_run (
    void
);

/* Prints a spec text with indentation. */
void spec_print (
    const cstr text
);

/* Prints a failed spec condition. */
void spec_failed (
    const cstr text,
    const cstr file,
    int line
);

/* Prints a verified spec condition. */
void spec_verified (
    void
);
