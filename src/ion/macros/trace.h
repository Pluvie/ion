/**
 * Traces the current `file` and `line` in the error.
 *
 * Useful to overwrite a lower level code error trace with higher (and more meaningful)
 * application level trace. */
#define trace() {           \
  error.file = __FILE__;    \
  error.line = __LINE__;    \
}
