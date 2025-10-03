#include "../framework.h"

static char* example_string = "abc";
static void* example_pointer = nullptr;

#ifdef  PRINT_STREAM_DEFAULT
#undef  PRINT_STREAM_DEFAULT
#define PRINT_STREAM_DEFAULT  tmp
#endif
