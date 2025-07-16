#define pipe_open(piper) \
  if (unlikely(pipe((int32*) piper) == -1)) { \
    fail("unable to open pipe: %s", strerror(errno)); \
  }
