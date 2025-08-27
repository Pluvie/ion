static inline void json_decode_enum (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  return json_decode_int(obj, io, rfx, allocator);
}
