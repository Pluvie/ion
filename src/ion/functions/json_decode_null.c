static inline bool json_decode_null (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return false;

  int result = json_parse_null(io);
  if (unlikely(failure.occurred))
    return false;

  if (result < 0)
    return false;

  zero_out(obj, rfx->size);

  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    return false;

  return true;
}
