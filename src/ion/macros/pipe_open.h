#if defined(__WIN32__)
  #error "Not implemented for Windows platform."

#elif defined(__APPLE__)
  #error "Not implemented for Apple platform."

#elif defined(__linux__)
  #define pipe_open(piper) \
    if (unlikely(pipe((int32*) piper) == -1)) { \
      fail("unable to open pipe: %s", strerror(errno)); \
    }

#else
  #error "Unsupported platform."
#endif
