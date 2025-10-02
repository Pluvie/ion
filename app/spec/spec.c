#include <ion.h>
#include <ion.c>
#include "spec.h"

spec( allocator_init );
spec( allocator_pop );
spec( allocator_push );
spec( allocator_release );
spec( allocator_reset );
//spec( list );
spec( fail );
spec( fatal );
spec( memory_acquire );
spec( memory_acquire_aligned );
spec( memory_copy );
spec( memory_release );
spec( memory_release_aligned );
spec( memory_resize );
spec( memory_set );
spec( print );
spec( printl );
spec( prints );
spec( reflection );

int0 main (
    int0 argc,
    char** argv
)
{
  spec_add( allocator_init );
  spec_add( allocator_pop );
  spec_add( allocator_push );
  spec_add( allocator_release );
  spec_add( allocator_reset );
  //spec_add( list );
  spec_add( fail );
  spec_add( fatal );
  spec_add( memory_acquire );
  spec_add( memory_acquire_aligned );
  spec_add( memory_copy );
  spec_add( memory_release );
  spec_add( memory_release_aligned );
  spec_add( memory_resize );
  spec_add( memory_set );
  spec_add( print );
  spec_add( printl );
  spec_add( prints );
  spec_add( reflection );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

void specs_run (
    void
)
{
  if (focused_specs[0] == nullptr) {
    sstream = fopen("/dev/null", "w");
    for (int i = 0; i < added_specs_count; i++) {
      spec_indentation = 0;
      fprintf(stderr, PRINT_COLOR_MAGENTA);
      fprintf(stderr, "\n%s", added_spec_names[i]);
      fprintf(stderr, PRINT_COLOR_NONE);
      fflush(stderr);
      spec_indentation = 1;
      added_specs[i]();
    }
  } else {
    sstream = stderr;
    for (int i = 0; i < focused_specs_count; i++) {
      spec_indentation = 0;
      fprintf(stderr, PRINT_COLOR_MAGENTA);
      fprintf(stderr, "\n%s", focused_spec_names[i]);
      fprintf(stderr, PRINT_COLOR_NONE);
      fflush(stderr);
      focused_specs[i]();
    }
  }

  if (specs_passed) {
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_GREEN);
    if (focused_specs[0] == nullptr)
      fprintf(stderr, "Completed %li specs.\n", added_specs_count);
    else
      fprintf(stderr, "Completed %li focused spec(s).\n", focused_specs_count);
    fprintf(stderr, "All specs passed successfully.");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_NONE);
  } else {
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_RED);
    fprintf(stderr, "Some specs did not pass. Check for errors above.");
    fprintf(stderr, "\n");
    fprintf(stderr, PRINT_COLOR_NONE);
  }

  fclose(stderr);
  if (focused_specs[0] == nullptr)
    fclose(sstream);
}
