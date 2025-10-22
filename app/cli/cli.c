#include "cli.h"
#include <ion.c>

#define set_of char*
#define set_cmp_function(v, u) cstr_equal(v, u)
#define set_hash_function(v) hash_djb2_cstr(v)
#include <ion/containers/set.c>

#define map_of char*, char*
#include <ion/containers/map.c>

map<char*, char*> argv_options_parse (
    int argc,
    char** argv,
    struct allocator* allocator
)
{
  map<char*, char*> options = map_alloc(char*, char*, argc, allocator);

  for (unsigned int i = 0; i < argc; i++) {
    char* option = argv[i];
    if (*option != '-')
      continue;

    char* value = i+1 < argc ? argv[i+1] : "";
    if (*value != '-')
      map_set(&options, option, value);
    else
      map_set(&options, option, "");
  }

  return options;
}
