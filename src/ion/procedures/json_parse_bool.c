
  if (io_contains(io, "true", lengthof("true"))) {
#ifndef JSON_DISCARD
    *result = true;
#else
    return true;
#endif
  }

  if (io_contains(io, "false", lengthof("false"))) {
#ifndef JSON_DISCARD
    *result = false;
#else
    return true;
#endif
  }

#ifndef JSON_DISCARD
#else
  return false;
#endif
