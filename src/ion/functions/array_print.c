void array_print (
    struct array* ary
)
{
  initialize(element, void*, NULL);

  for (initialize(index, u64, 0); index < ary->length; increment(index)) {
    call(fprintf, stderr, "-----------\n");
    call(fprintf, stderr, "%9li |\n", index);
    call(fprintf, stderr, "-----------\n");

    assign_to(element, array_get(ary, index));

    if (element == NULL) {
      call(fprintf, stderr, "         --\n");
      continue;
    }

    call(hexdump, element, ary->typesize);
  }
}
