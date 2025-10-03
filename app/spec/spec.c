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
