void str_append (
    str* source,
    str target
)
{
  memory_copy(source->chars + source->length, target.chars, target.length);
  source->length += target.length;
}
