static inline void csv_decode_row (
    void* row_obj,
    struct io* source,
    struct reflection* row_rfx,
    struct memory* allocator
)
{
  struct csv_properties* csv = row_rfx->support_data;

  struct memory row_allocator = memory_init(0);
  struct array* columns = csv_parse_row(source, &row_allocator, csv);

  struct reflection* field_rfx = NULL;
  for array_each(csv->headers, struct reflection**, header, header_index) {
    field_rfx = *header;
    if (field_rfx == NULL)
      continue;

    void* field_obj = row_obj + field_rfx->offset;
    struct string* column = array_get(columns, header_index);

    switch (field_rfx->type) {
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
      string_to_number(column, field_rfx->type, field_obj);
      if (error.occurred)
        return;

      continue;

    case BOOL:
      if (strneq("false", column->content, lengthof("false")))
        memcpy(field_obj, &(bool) { false }, field_rfx->size);
      else
        memcpy(field_obj, &(bool) { true }, field_rfx->size);

      continue;

    case STRING:
      struct string* string = field_obj;
      string->content = memory_alloc(allocator, column->length + 1);
      string->length = column->length;
      memcpy(string->content, column->content, column->length);
      string->content[string->length] = '\0';

      continue;

    default:
      continue;
    }
  }

  memory_release(&row_allocator);
}
