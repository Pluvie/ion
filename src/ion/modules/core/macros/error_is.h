/**
 * Checks the error message. */
#define error_is(expected_message) \
  (strncmp(error.message, expected_message, lengthof(expected_message)) == 0)
