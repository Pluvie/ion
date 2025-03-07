static inline void reflection_initialize (
    struct reflection* rfx,
    void* target,
    struct memory* allocator
)
{
  rfx->target = target;
  rfx->allocator = allocator;

  switch (rfx->type) {
  case STRUCT:
    for vector_each(rfx->fields, struct reflection*, field_rfx) {
      field_rfx->parent = rfx;
      void* field_target = rfx->target + field_rfx->offset;
      reflection_initialize(field_rfx, field_target, allocator);
    }

    break;

  case ARRAY:
  case POINTER:
  case SEQUENCE:
  case VECTOR:
    struct reflection* element_rfx = rfx->element;
    element_rfx->parent = rfx;
    reflection_initialize(element_rfx, target, allocator);

    if (rfx->type == SEQUENCE)
      rfx->length = rfx->size / element_rfx->size;

    break;

  default:
    break;
  }

  return;
}
