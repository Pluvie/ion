test( reflection_macros, sequence_type ) {

  given("a sequence");
    u32 cube[3][3][3];


  calling("the reflection macros");
    struct reflection rfx = {
      type(SEQUENCE, u32[3][3][3]), of({ type(U32) })
    };


  must("correctly define the reflection");
    verify(rfx.type == SEQUENCE);
    verify(rfx.size == sizeof(cube));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.name == NULL);
    verify(rfx.element != NULL);

    struct reflection* element_rfx = rfx.element;
    verify(element_rfx->type == U32);
    verify(element_rfx->size == sizeof(u32));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);


  success();
}
