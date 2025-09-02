
  if (io_contains(io, "null", lengthof("null")))
    goto parse_success;

  goto parse_failure;
