void  memory_release (
    void* address
)
{
#if platform(LINUX)
  #include "../platform/linux/functions/memory_release.c"
#endif
}
