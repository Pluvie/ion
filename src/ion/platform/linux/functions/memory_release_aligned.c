void platform_memory_release_aligned (
    void* aligned_address
)
{
  free(aligned_address);
}
