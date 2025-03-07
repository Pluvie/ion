test( reflection_macros, struct_type ) {

  given("a struct");
    struct example {
      u64 value_u64;
      d64 value_d64;
    };


  calling("the reflection macros");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(value_u64, U64, struct example) },
        { field(value_d64, D64, struct example) },
      }),
    };


  must("correctly define the reflection");
    verify(rfx.type == STRUCT);
    verify(rfx.size == sizeof(struct example));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.name == NULL);
    verify(rfx.fields != NULL);
    verify(rfx.fields->length == 2);

    struct reflection* field_rfx;
    field_rfx = vector_get(rfx.fields, 0);
    verify(field_rfx->type == U64);
    verify(field_rfx->size == sizeof(u64));
    verify(field_rfx->offset == offsetof(struct example, value_u64));
    verify(field_rfx->index == 0);

    field_rfx = vector_get(rfx.fields, 1);
    verify(field_rfx->type == D64);
    verify(field_rfx->size == sizeof(d64));
    verify(field_rfx->offset == offsetof(struct example, value_d64));
    verify(field_rfx->index == 0);


  success();
}
