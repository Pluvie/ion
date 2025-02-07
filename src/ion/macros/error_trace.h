/**
 * Traces the current `file` and `line` of an error. */
#define error_trace() (                               \
  error.trace[error.trace_count].file = __FILE__,     \
  error.trace[error.trace_count].line = __LINE__,     \
  error.trace_count < ERROR_TRACE_CAP - 1 ?           \
    (error.trace_count++) :                           \
    (error.trace_count = ERROR_TRACE_CAP - 1)         \
)
