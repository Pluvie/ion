static inline void json_decode_primitive (
    void* obj,
    struct io* io,
    struct reflection* rfx,
    struct memory* allocator
)
{
  switch (rfx->type) {
  case U8:
  case U16:
  case U32:
  case U64:
  case I8:
  case I16:
  case I32:
  case I64:
  case D32:
  case D64:
  case D128:
    u64 number_length = json_parse_number(io);
    if (error.occurred)
      return error_add_reflection_path(rfx);

    if (number_length == 0) {
      fail("expected a number");
      error_add_io_extraction(io);
      error_add_reflection_path(rfx);
      return;
    }

    void* number_content = io_read(io, number_length);
    if (error.occurred) {
      error_add_reflection_path(rfx);
      return;
    }

    struct string number = string_init(number_length, allocator);
    memcpy(number.content, number_content, number_length);
    string_to_number(&number, rfx->type, obj);

    if (error.occurred) {
      error_add_io_extraction(io);
      error_add_reflection_path(rfx);
      return;
    }

    break;

  case BOOL:
    u64 bool_length = json_parse_bool(io);
    if (error.occurred)
      return;

    if (bool_length > 0)
      io_read(io, bool_length);

    if (error.occurred)
      return;

    switch (bool_length) {
    case lengthof("true"):
      memcpy(obj, &(bool) { true }, sizeof(bool));
      break;

    case lengthof("false"):
      memcpy(obj, &(bool) { false }, sizeof(bool));
      break;

    default:
      fail("expected a boolean");
      error_add_io_extraction(io);
      error_add_reflection_path(rfx);
      return;
    }

    break;

  default:
    fail("primitive type `%s` not supported in json", type_names[rfx->type]);
    error_add_io_extraction(io);
    error_add_reflection_path(rfx);
    return;
  }
  
  reflection_validate(rfx, obj);
  if (error.occurred)
    return error_add_reflection_path(rfx);
}
