struct reflection* reflection_field_find (
    struct reflection* reflection,
    str* field_name
)
{
  struct reflection* field = reflection->fields;
  while (field != nullptr) {
    if (str_equal(field->name, *field_name))
      field->parent = reflection;
      return field;
    }

    field++;
  }

  return nullptr;
}
