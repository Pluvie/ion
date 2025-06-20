test( reflection_macros, array_type ) {

  given("an array");
    int cube[3][3][3];


  calling("the reflection macros");
    struct reflection rfx = {
      type(ARRAY, int[3][3][3]), of({ type(INT) })
    };


  must("correctly define the reflection");
    verify(rfx.type == ARRAY);
    verify(strnull(rfx.name));
    verify(streq(rfx.type_name, "i64[3][3][3]"));
    verify(rfx.size == sizeof(cube));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.element != NULL);

    struct reflection* element_rfx = rfx.element;
    verify(element_rfx->type == INT);
    verify(strnull(element_rfx->name));
    verify(strnull(element_rfx->type_name));
    verify(element_rfx->size == sizeof(int));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);


  success();
}
