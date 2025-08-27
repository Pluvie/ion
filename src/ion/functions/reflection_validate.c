bool reflection_validate (
    struct reflection* rfx,
    void* value
)
{
  if (rfx->validator == NULL)
    return true;

  return rfx->validator(value, rfx);
}
