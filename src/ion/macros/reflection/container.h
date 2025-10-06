/*
  Defines the container used for reflection.
*/
#define container(n, T) \
  .container = { n<T>_reflection_creator, n<T>_reflection_adder }
