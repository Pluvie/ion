void reflection_inspect_indentation (
    struct reflection* rfx,
    void* object,
    u32 indentation
)
{
  if (rfx->parent == NULL || rfx->parent->type != POINTER)
    for (u32 i = 0; i < indentation; i++)
      emit(" ");

  if (rfx->name != NULL)
    emit("%.*s", sp(rfx->name));

  reflection_inspect_type(rfx);
  reflection_inspect_value(rfx, object, indentation);
}
