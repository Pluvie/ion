test( reflection_macros, struct_type ) {

  given("a struct");
    struct example {
      int value_int;
      dec value_dec;
    };


  calling("the reflection macros");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(value_int, INT, struct example) },
        { field(value_dec, DEC, struct example) },
      }),
    };


  must("correctly define the reflection");
    verify(rfx.type == STRUCT);
    verify(strnull(rfx.name));
    verify(streq(rfx.type_name, "struct example"));
    verify(rfx.size == sizeof(struct example));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.fields != NULL);
    verify(rfx.fields->length == 2);

    struct reflection* field_rfx;
    field_rfx = list_at(rfx.fields, 0);
    verify(field_rfx->type == INT);
    verify(streq(field_rfx->name, "value_int"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(int));
    verify(field_rfx->offset == offsetof(struct example, value_int));
    verify(field_rfx->index == 0);

    field_rfx = list_at(rfx.fields, 1);
    verify(field_rfx->type == DEC);
    verify(streq(field_rfx->name, "value_dec"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(dec));
    verify(field_rfx->offset == offsetof(struct example, value_dec));
    verify(field_rfx->index == 0);


  success();
}
