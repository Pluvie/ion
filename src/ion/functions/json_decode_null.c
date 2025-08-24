bool json_decode_null (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    goto error;

  int null_length = json_parse_null(io);
  if (unlikely(failure.occurred))
    goto error;

  if (null_length <= 0)
    return false;

  io_read(io, null_length);
  if (unlikely(failure.occurred))
    goto error;

  memzero(obj, rfx->size);

  json_parse_spaces(io);
  if (unlikely(failure.occurred))
    goto error;

  return true;

error:
  return true;
}
