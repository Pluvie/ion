#include "spec_framework.h"

/*
  Creates a spec-specific copy of the function so that the linker does not find
  multiple definitions of this function with the same name.
*/
#define fail  specced__fail
#include "../ion/functions/fail.c"
