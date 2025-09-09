static inline int clz (
    int number
)
{
#if   INT_SIZE == 64
  return (int) __builtin_clzll(number);
#elif INT_SIZE == 32
  return (int) __builtin_clzl(number);
#endif
}
