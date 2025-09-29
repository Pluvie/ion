/*
  By default, the stream where `print` and `printl` macros operate is stderr.
  This can be changed by defining the PRINT_STREAM_DEFAULT before including the
  ion.h header.
*/
#ifndef PRINT_STREAM_DEFAULT
#define PRINT_STREAM_DEFAULT  stderr
#endif

/*
  Defines some colors for printing on the tty.
*/
#define PRINT_COLOR_BLUE      "\x1b[34m"
#define PRINT_COLOR_CYAN      "\x1b[36m"
#define PRINT_COLOR_GREEN     "\x1b[32m"
#define PRINT_COLOR_GREY      "\e[38;5;250m"
#define PRINT_COLOR_MAGENTA   "\x1b[35m"
#define PRINT_COLOR_NONE      "\x1b[0m"
#define PRINT_COLOR_RED       "\x1b[31m"
#define PRINT_COLOR_YELLOW    "\x1b[33m"
