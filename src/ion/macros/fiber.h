/**
 * Helper to construct a fiber name. */
#define fiber(name) \
  fiber__ ## name
