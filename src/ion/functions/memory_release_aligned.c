void memory_release_aligned (
    void* aligned_address
)
{
  aligned_free(aligned_address);
}
