#include <ion.h>

/*
  Suppresses by default all spec printouts.
*/
#ifdef  PRINT_STREAM_DEFAULT
#undef  PRINT_STREAM_DEFAULT
#endif
#define PRINT_STREAM_DEFAULT sstream

/*
  Defines a function specification.
*/
#define spec(function) \
  void spec__ ## function (void)

/*
  Defines a function specification argument.
*/
#define argument(...) \
  __VA_OPT__(__VA_ARGS__;)

/*
  Defines a function specification precondition.
*/
#define precondition(cond) \
  spec_print("given " cond);

/*
  Applies a function specification precondition.
*/
#define apply(...) \
  __VA_OPT__(__VA_ARGS__)

/*
  Defines a function specification codepath.
*/
#define when(cond) \
  spec_print("when " cond); \
  spec_indentation++; \
  memset(&sim, 0, sizeof(sim));

/*
  Defines a function specification condition that must be verified.
*/
#define must(cond) \
  spec_print("must " cond " "); \
  spec_print_verification_enabled = true;

/*
  Verifies a condition.
*/
#define verify(cond) \
  if (!(cond)) { spec_failed(#cond, __FILE__, __LINE__ ); } else { spec_verified(); }

/*
  Defines a function specification codepath success.
*/
#define success() \
  spec_print_verification_enabled = false;

/*
  Ends a specification codepath.
*/
#define end() \
  spec_indentation--;

/*
  Defines a spec dependency.
*/
#define dependency(func) \
  dependency__ ## func

/*
  Defines a specced function copy.
*/
#define specced(func) \
  specced__ ## func

/*
  Global variable that stores the original value of stderr.
  All specs by default suppresses any printout.
*/
extern void* sstream;

/*
  Holds the current indentation level.
*/
extern int spec_indentation;

/*
  Global variable that enables/disables the printing of spec verifications.
*/
extern bool spec_print_verification_enabled;

/*
  Global variable that stores the final result of all specs.
*/
extern bool specs_passed;

/*
  Prints a spec text with indentation.
*/
void spec_print (
    const char* text
);

/*
  Prints a failed spec condition.
*/
void spec_failed (
    const char* text,
    const char* file,
    int line
);

/*
  Prints a verified spec condition.
*/
void spec_verified (
    void
);
