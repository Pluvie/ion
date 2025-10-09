/*
  Defines the container used for reflection.
*/
#define container(n, ...)               \
  .container = {                        \
    n<__VA_ARGS__>_reflection_creator,  \
    n<__VA_ARGS__>_reflection_adder,    \
  }
