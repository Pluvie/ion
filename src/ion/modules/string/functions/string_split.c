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
    u64 begin;
    u64 end;
    u64 length;
    char* content;
  } chunk = { 0 };

  u64 cursor = 0;
  bool in_wrap = false;
  bool last_chunk = false;

  struct array* chunks =
    array_allocate(sizeof(struct string), 0, allocator);

  if (unlikely(string.length == 0))
    return chunks;

read_chunk:
  if (cursor >= string.length - 1) {
    last_chunk = true;
    goto push_chunk;
  }

  if (wrapper != '\0' && string.content[cursor] == wrapper) {
    in_wrap = !in_wrap;
    cursor++;
    goto read_chunk;
  }

  if (in_wrap) {
    cursor++;
    goto read_chunk;
  }

  if (string.content[cursor] != separator) {
    cursor++;
    goto read_chunk;
  }

push_chunk:
  chunk.end = cursor;
  chunk.length = chunk.end - chunk.begin;

  if (unlikely(chunk.length == 0))
    goto terminate;

  if (last_chunk)
    chunk.length++;

  chunk.content = memory_alloc_zero(allocator, chunk.length + 1);
  snprintf(chunk.content, chunk.length + 1, "%s", string.content + chunk.begin);
  array_push(chunks, &(struct string) { chunk.content, chunk.length });

  if (last_chunk)
    goto terminate;
  
  memzero(&chunk, sizeof(chunk));
  chunk.begin = cursor + 1;

  cursor++;

  goto read_chunk;

terminate:
  return chunks;
}
