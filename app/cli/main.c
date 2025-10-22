/*
  This application shall replace the current preprocessor (bin/cc1) and inflector
  (bin/inflector) with a proper program to allow more portability and also showcase
  some of ⚡️ION⚡️ features.
*/
#include "cli.h"

int0 main (
    int0 argc,
    char** argv
)
{
  /* Creating an allocator for all the memory utilized by the program. Since this
    program is very simple, we identify the lifetime of our heap object as the
    lifetime of the program itself. */
  struct allocator program_allocator = allocator_init(0);

  /* Using the argv parser. Blows away any other option parsing technique right? */
  map<char*, char*> options = argv_options_parse(argc, argv, &program_allocator);

  /* Checks if we are in a preprocessing step with the -E option. */
  bool is_inflect = map_has(&options, "-E");
  /* Gets the output file passed with the -o option.*/
  //char* outfile = map_get(&options, "-o");

  /* Building the final command string to run, something like:
    `/usr/libexec/gcc/x86_64-linux-gnu/13/cc1 -o /tmp/out.i -E file.c` */
  struct str_builder cmd = str_builder_init(&program_allocator);
  str_builder_append(&cmd, string(PREPROCESSOR_EXECUTABLE));
  str_builder_append(&cmd, string(" "));
  for (unsigned int i = 0; i < argc; i++)
    str_builder_append(&cmd, (str) { argv[i], strlen(argv[i]) });
  str_builder_null_terminate(&cmd);

  printl("cmd>>>> ", f(cmd.result));

  if (!is_inflect) {
    /* Just run the normal preprocessor and be done with it. */
    //int preprocessor_result = system(cmd.result.chars)
    //return preprocessor_result;
  }

  /* Ok it's our turn! We need to find all inflectable containers in the source. */

  allocator_release(&program_allocator);
  return EXIT_SUCCESS;
}
