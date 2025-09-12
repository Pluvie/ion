void* memory_resize (
    void* address,
    int amount,
    int alignment
)
{
#if platform(LINUX)
  #include "../platform/linux/functions/memory_resize.c"
#endif
}
