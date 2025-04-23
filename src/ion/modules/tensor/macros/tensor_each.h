/**
 * Loops through the elements of a tensor. */
#define tensor_each(tensor, iter)                                                       \
  (; iter.index < (tensor)->length; iter.index++)                                       \
    if (iter.value = (tensor)->data + iter.index, true)
