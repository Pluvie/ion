static inline void csv_decode_row (
    struct io* source,
    struct reflection* struct_rfx,
    struct array* headers,
    struct csv_properties csv
)
{
  struct memory row_allocator = memory_init(0);
  struct array* columns = csv_parse_row(source, &row_allocator, csv);

  struct reflection* field_rfx = NULL;
  for array_each_with_index(headers, header_index, struct reflection**, header) {
    field_rfx = *header;
    if (field_rfx == NULL)
      continue;

    field_rfx->target = struct_rfx->target + field_rfx->offset;
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
      string_to_number(column, field_rfx->type, field_rfx->target);
      if (error.occurred)
        return;

      continue;

    case BOOL:
      if (strneq("false", column->content, lengthof("false")))
        memcpy(field_rfx->target, &(bool) { false }, field_rfx->size);
      else
        memcpy(field_rfx->target, &(bool) { true }, field_rfx->size);

      continue;

    case STRING:
      struct string* string = field_rfx->target;
      string->content = memory_alloc(field_rfx->allocator, column->length + 1);
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
