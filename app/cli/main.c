/*
  This application shall replace the current preprocessor (bin/cc1) and inflector
  (bin/inflector) with a proper program to allow more portability and also showcase
  some of ⚡️ION⚡️ features.
*/

#include <ion.h>
#include "cli.h"

int0 main (
    int0 argc,
    char** argv
)
{
  /* Using the argv parser. Blows away any other option parsing technique right? */
  map<char*, char*> opts = argv_parse(argv, argc);

  char* outfile   = map_get(opts, "-o");
  bool is_inflect = map_has(opts, "-E");

  if (!is_inflect) {
    /* Just run the normal preprocessor and be done with it. */
    int preprocessor_result = ...
    return preprocessor_result;
  }

  /* To be continued. */
}
