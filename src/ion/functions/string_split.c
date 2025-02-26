#ifdef ION_INCLUDED
static inline
#endif

struct array* string_split (
    struct string string,
    struct memory* allocator,
    char separator,
    char wrapper
)
{
  struct {
    i32 begin;
    i32 end;
    i32 length;
    char* content;
  } chunk = { 0 };

  i32 cursor = 0;

  struct array* chunks =
    array_allocate(sizeof(struct string), 0, allocator);

read_chunk:
  if (cursor >= string.length - 1)
    goto push_chunk;

  if (string.content[cursor] != separator) {
    cursor++;
    goto read_chunk;
  }

push_chunk:
  chunk.end = cursor;
  chunk.length = chunk.end - chunk.begin;

  if (unlikely(chunk.length == 0))
    goto terminate;

  chunk.content = memory_alloc_zero(allocator, chunk.length + 1);
  snprintf(chunk.content, chunk.length + 1, "%s", string.content + chunk.begin);
  array_push(chunks, &(struct string) { chunk.content, chunk.length });
  
  memzero(&chunk, sizeof(chunk));
  chunk.begin = cursor + 1;

  cursor++;

  goto read_chunk;

terminate:
  return chunks;
}
