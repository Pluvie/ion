struct reflection* reflection_field_find (
    struct reflection* reflection,
    str* field_name
)
{
  struct reflection* field = reflection->fields;
  while (field->type != 0) {
    if (str_equal(field->name, *field_name)) {
      field->parent = reflection;
      return field;
    }

    field++;
  }

  return nullptr;
}
