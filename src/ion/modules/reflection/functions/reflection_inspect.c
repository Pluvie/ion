void reflection_inspect (
    struct reflection* rfx,
    struct string* name,
    void* object
)
{
  print("");
  struct string* original_rfx_name = rfx->name;

  rfx->name = name;
  reflection_inspect_indentation(rfx, object, 0);
  rfx->name = original_rfx_name;
}
