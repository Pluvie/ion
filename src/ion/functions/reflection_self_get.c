struct reflection* reflection_self_get (
    struct reflection* rfx
)
{
  if (rfx->self != NULL)
    return rfx;

  if (rfx->parent == NULL) {
    rfx->self = rfx;
    return rfx;
  }

  return reflection_self_get(rfx->parent);
}
