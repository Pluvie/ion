test( reflection_macros, list_type_nested ) {

  given("a list");
    list<list<int>> table;


  calling("the reflection macros");
    struct reflection rfx = {
      type(LIST), of({
        type(LIST), of({
          type(INT)
        }),
      }),
    };


  must("correctly define the reflection");
    verify(rfx.type == LIST);
    verify(rfx.size == sizeof(table));
    verify(strnull(rfx.name));
    verify(strnull(rfx.type_name));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.element != NULL);

    struct reflection* element_rfx = rfx.element;
    verify(element_rfx->type == LIST);
    verify(strnull(element_rfx->name));
    verify(strnull(element_rfx->type_name));
    verify(element_rfx->size == sizeof(list<int>));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->element != NULL);

    element_rfx = element_rfx->element;
    verify(element_rfx->type == INT);
    verify(strnull(element_rfx->name));
    verify(strnull(element_rfx->type_name));
    verify(element_rfx->size == sizeof(int));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);


  success();
}
