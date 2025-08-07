static inline void json_decode_set (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  return json_decode_list(obj, io, rfx, allocator);
}
