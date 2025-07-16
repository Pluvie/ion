#define pipe_close(piper) \
  close((piper)->reader); \
  close((piper)->writer);
