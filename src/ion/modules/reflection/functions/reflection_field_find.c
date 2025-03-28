struct reflection* reflection_field_find (
    struct reflection* rfx,
    struct string* field_name
)
{
  for vector_each(rfx->fields, struct reflection*, field_rfx) {
    if (strneq(field_rfx->name->content, field_name->content, field_name->length)) {
      field_rfx->parent = rfx;
      return field_rfx;
    }
  }

  return NULL;
}
