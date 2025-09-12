void* memory_require (
    int amount,
    int alignment
)
{
#if platform(LINUX)
  #include "../platform/linux/functions/memory_require.c"
#endif
}
