void json_encode_struct (
    void* obj,
    struct io* io,
    struct reflection* rfx
)
{
  io_write(io, "{", 1);
  if (unlikely(failure.occurred))
    return;

  for vector_each(rfx->fields, struct reflection*, field_rfx, field_index) {
    if (field_index > 0) {
      io_write(io, ",", 1);
      if (unlikely(failure.occurred))
        return;
    }

    field_rfx->parent = rfx;
    io_write(io, "\"", 1);
    if (unlikely(failure.occurred))
      return;

    io_write(io, field_rfx->name->content, field_rfx->name->length);
    if (unlikely(failure.occurred))
      return;

    io_write(io, "\"", 1);
    if (unlikely(failure.occurred))
      return;

    io_write(io, ":", 1);
    if (unlikely(failure.occurred))
      return;

    void* field_obj = obj + field_rfx->offset;
    json_encode(field_obj, io, field_rfx);
    if (unlikely(failure.occurred))
      return;
  }

  io_write(io, "}", 1);
  if (unlikely(failure.occurred))
    return;
}
