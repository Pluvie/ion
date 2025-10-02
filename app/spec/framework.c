#include <ion.h>

/*
  Holds the current indentation level.
*/
extern int spec_indentation;

/*
  Global variable that stores the final result of all specs.
*/
extern bool specs_passed;

/*
  Global variable that enables/disables the printing of spec verifications.
*/
extern bool spec_print_verification_enabled;

/*
  Prints a spec text with indentation.
*/
void spec_print (
    const char* text
)
{
  fprintf(stderr, "\n");

  for (int i = 0; i < spec_indentation; i++)
    fprintf(stderr, "  ");
    
  fprintf(stderr, "%s", text);
}

/*
  Prints a failed spec condition.
*/
void spec_failed (
    const char* text,
    const char* file,
    int line
)
{
  specs_passed = false;
  fprintf(stderr, PRINT_COLOR_RED);
  fprintf(stderr, "█");
  fprintf(stderr, PRINT_COLOR_NONE);
  fprintf(stderr, "\n");
  for (int i = 0; i < spec_indentation; i++)
    fprintf(stderr, "  ");
  fprintf(stderr, PRINT_COLOR_RED);
  fprintf(stderr, "%s (%s:%li) ", text, file, line);
  fprintf(stderr, PRINT_COLOR_NONE);
}

/*
  Prints a verified spec condition.
*/
void spec_verified (
    void
)
{
  if (spec_print_verification_enabled) {
    fprintf(stderr, PRINT_COLOR_GREEN);
    fprintf(stderr, "█");
    fprintf(stderr, PRINT_COLOR_NONE);
  }
}
