struct reflection* reflection_field_find (
    struct reflection* rfx,
    string field_name
)
{
  for list_each(rfx->fields, struct reflection* field_rfx) {
    if (streq(field_rfx->name, field_name)) {
      field_rfx->parent = rfx;
      return field_rfx;
    }
  }

  return NULL;
}
