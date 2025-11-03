uint str_append (
    str* source,
    str target
)
{
  uint appendable_amount = source->length;
  if (target.length < source->length)
    appendable_amount = target.length;

  memory_copy(source->chars, target.chars, appendable_amount);
  source->chars += appendable_amount;
  source->length -= appendable_amount;

  return appendable_amount;
}
