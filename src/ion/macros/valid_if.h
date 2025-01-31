/**
 * Used to link a schema validator. */
#define valid_if(validator_function) \
  .validator = validator_function
