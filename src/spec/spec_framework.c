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
  fprintf(sstream, "\n");

  for (int i = 0; i < spec_indentation; i++)
    fprintf(sstream, "  ");
    
  fprintf(sstream, "%s", text);
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
  fprintf(sstream, PRINT_COLOR_RED);
  fprintf(sstream, "█");
  fprintf(sstream, PRINT_COLOR_NONE);
  fprintf(sstream, "\n");
  for (int i = 0; i < spec_indentation; i++)
    fprintf(sstream, "  ");
  fprintf(sstream, PRINT_COLOR_RED);
  fprintf(sstream, "%s (%s:%li) ", text, file, line);
  fprintf(sstream, PRINT_COLOR_NONE);
}

/*
  Prints a verified spec condition.
*/
void spec_verified (
    void
)
{
  if (spec_print_verification_enabled) {
    fprintf(sstream, PRINT_COLOR_GREEN);
    fprintf(sstream, "█");
    fprintf(sstream, PRINT_COLOR_NONE);
  }
}
