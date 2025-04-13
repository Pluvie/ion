#include "suites/core.c"
#include "suites/array.c"
//#include "suites/io.c"
#include "suites/map.c"
#include "suites/set.c"
#include "suites/time.c"
#include "suites/tensor.c"
//#include "suites/reflection.c"
//#include "suites/binary.c"
//#include "suites/csv.c"
//#include "suites/json.c"
//#include "suites/tcp.c"
//#include "suites/http.c"

bool suite_register (
    i32 argc,
    char** argv
)
{
  if (argc == 2)
    goto run_specific_suite;

  test_suite__core();
  test_suite__array();
  //test_suite__io();
  test_suite__map();
  test_suite__set();
  test_suite__time();
  test_suite__tensor();
  //test_suite__reflection();
  //test_suite__binary();
  //test_suite__csv();
  //test_suite__json();
  //test_suite__tcp();
  //test_suite__http();

  return true;

run_specific_suite:
  char* module = argv[1];

        if (strcmp(module, "core") == 0)
    test_suite__core();
  else  if (strcmp(module, "array") == 0)
    test_suite__array();
  //else  if (strcmp(module, "io") == 0)
  //  test_suite__io();
  else  if (strcmp(module, "map") == 0)
    test_suite__map();
  else  if (strcmp(module, "set") == 0)
    test_suite__set();
  else  if (strcmp(module, "time") == 0)
    test_suite__time();
  else  if (strcmp(module, "tensor") == 0)
    test_suite__tensor();
  //else  if (strcmp(module, "reflection") == 0)
  //  test_suite__reflection();
  //else  if (strcmp(module, "binary") == 0)
  //  test_suite__binary();
  //else  if (strcmp(module, "csv") == 0)
  //  test_suite__csv();
  //else  if (strcmp(module, "json") == 0)
  //  test_suite__json();
  //else  if (strcmp(module, "tcp") == 0)
  //  test_suite__tcp();
  //else  if (strcmp(module, "http") == 0)
  //  test_suite__http();
  else
    goto unrecognized_module;

  return true;

unrecognized_module:
  fprintf(original_stderr, "\n");
  fprintf(original_stderr, PRINT_COLOR_RED);
  fprintf(original_stderr, "Unrecognized module: `%s`.", module);
  fprintf(original_stderr, "\n");
  fprintf(original_stderr, PRINT_COLOR_NONE);

  return false;
}
