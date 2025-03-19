#ifdef ION_INCLUDED
static inline
#endif

struct string* string_allocate (
    u64 length,
    struct memory* allocator
)
{
  struct string* string = memory_alloc(allocator, sizeof(struct string));
  string->content = memory_alloc(allocator, length + 1);
  string->length = length;
  string->content[string->length] = '\0';
  return string;
}
