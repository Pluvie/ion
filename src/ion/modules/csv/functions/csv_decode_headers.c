static inline struct array* csv_decode_headers (
    struct io* source,
    struct reflection* struct_rfx,
    struct csv_properties csv
)
{
  u64 initial_cursor_position = source->cursor;
  bool at_least_one_matching_header = false;
  io_flag_add(source, IO_FLAGS_BUFFER_RETAIN);

  struct array* columns = csv_parse_row(source, struct_rfx->allocator, csv);
  struct array* headers = array_allocate(
    sizeof(addr), columns->length, struct_rfx->allocator);

  for array_each(columns, struct string*, column) {
    bool matching_field = false;

    for vector_each(struct_rfx->fields, struct reflection*, field_rfx) {
      if (strneq(column->content, field_rfx->name->content, column->length)) {
        matching_field = true;
        at_least_one_matching_header = true;

        addr field_rfx_addr = (addr) field_rfx;
        array_push(headers, &field_rfx_addr);
        break;
      }
    }

    if (!matching_field)
      array_push(headers, &(addr) { 0 });
  }

  io_flag_remove(source, IO_FLAGS_BUFFER_RETAIN);
  if (at_least_one_matching_header)
    return headers;

  
  for vector_each(struct_rfx->fields, struct reflection*, field_rfx, field_index) {
    addr field_rfx_addr = (addr) field_rfx;
    array_set(headers, field_index, &field_rfx_addr);
  }

  source->cursor = initial_cursor_position;
  return headers;
}
