#if defined(__WIN32__)
  #error "Not implemented for Windows platform."

#elif defined(__APPLE__)
  #error "Not implemented for Apple platform."

#elif defined(__linux__)
  #define pipe_close(piper) \
    close((piper)->reader); \
    close((piper)->writer);

#else
  #error "Unsupported platform."
#endif
