#include <ion.h>

#define set_of char*
#include <ion/containers/set.h>

#define map_of char*, char*
#include <ion/containers/map.h>

#if standard(>= C11)
#define map_function(type, func, ...)               \
  _Generic(type,                                    \
    map<char*, char*> : map<char*, char*>_ ## func  \
  )
#endif

#define PREPROCESSOR_EXECUTABLE "/usr/libexec/gcc/x86_64-linux-gnu/13/cc1"

map<char*, char*> argv_options_parse (
    int argc,
    char** argv,
    struct allocator* allocator
);
