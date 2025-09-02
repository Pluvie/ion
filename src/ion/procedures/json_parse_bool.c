
  if (io_contains(io, "true", lengthof("true"))) {
#ifndef JSON_DISCARD
    *result = true;
#endif
    goto parse_success;
  }

  if (io_contains(io, "false", lengthof("false"))) {
#ifndef JSON_DISCARD
    *result = false;
#endif
    goto parse_success;
  }

  goto parse_failure;
