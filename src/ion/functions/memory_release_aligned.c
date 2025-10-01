void memory_release_aligned (
    void* aligned_address
)
{
#if standard(>= C11)
  aligned_free(aligned_address);

#else
  /*
    C99 compliant implementation of `aligned_alloc`.

    Frees the address stored just before the `aligned_address`. This was the original
    address returned by malloc. See `memory_acquire_aligned` for more details.
  */
  free(aligned_address - sizeof(void*));

#endif
}
