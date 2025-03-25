/**
 * Padding for structs. */
#define padding(amount) \
  unsigned char cvar(__padding)[amount];
