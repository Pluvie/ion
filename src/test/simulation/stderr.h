/**
 * @file
 * This file suppresses all printouts to stderr, so that only test relevant info shall
 * be printed when running the suite. */




FILE* tmp_stderr;
FILE* original_stderr;
FILE* suppressed_stderr;




#undef stderr
#define stderr suppressed_stderr
