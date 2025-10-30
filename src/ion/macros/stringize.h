/* Stringize any token or definition. */
#define stringize_indirection(v) #v
#define stringize(v) stringize_indirection(v)
