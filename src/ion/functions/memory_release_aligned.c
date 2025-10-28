void memory_release_aligned (
    void* aligned_address
)
{
#if standard(>= C11)
#if platform(WINDOWS)
  _aligned_free(aligned_address);
#else
  free(aligned_address);
#endif

#else
  /* C89/C99 compliant implementation of `aligned_free`.

    Frees the address stored just before the `aligned_address`. This was the original
    address returned by malloc. See `memory_acquire_aligned` for more details. */
  free(((byte*) aligned_address) - sizeof(void*));

#endif
}
