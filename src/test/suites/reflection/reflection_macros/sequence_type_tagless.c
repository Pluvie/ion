test( reflection_macros, sequence_type_tagless ) {

  given("a struct");
    struct example {
      u64 value_u64;
      struct {
        i64 value_i64;
        d64 value_d64;
      } why[3];
    };


  calling("the reflection macros");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(value_u64, U64, struct example) },
        { field(why, SEQUENCE, struct example), of({
            type(STRUCT, typeof(*o(struct example)->why)), fields({
              { field(value_i64, I64, typeof(*o(struct example)->why)) },
              { field(value_d64, D64, typeof(*o(struct example)->why)) },
            })
          })
        },
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
    verify(string_equal(field_rfx->name, &s("value_u64")));
    verify(field_rfx->index == 0);

    field_rfx = vector_get(rfx.fields, 1);
    verify(field_rfx->type == SEQUENCE);
    verify(field_rfx->size == sizeof(o(struct example)->why));
    verify(field_rfx->offset == offsetof(struct example, why));
    verify(string_equal(field_rfx->name, &s("why")));
    verify(field_rfx->index == 0);
    verify(field_rfx->element != NULL);

    struct reflection* element_rfx;
    element_rfx = field_rfx->element;
    verify(element_rfx->type == STRUCT);
    verify(element_rfx->size == sizeof(*o(struct example)->why));
    verify(element_rfx->offset == 0);
    verify(element_rfx->name == NULL);
    verify(element_rfx->index == 0);
    verify(element_rfx->fields != NULL);
    verify(element_rfx->fields->length == 2);

    field_rfx = vector_get(element_rfx->fields, 0);
    verify(field_rfx->type == I64);
    verify(field_rfx->size == sizeof(i64));
    verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_i64));
    verify(string_equal(field_rfx->name, &s("value_i64")));
    verify(field_rfx->index == 0);

    field_rfx = vector_get(element_rfx->fields, 1);
    verify(field_rfx->type == D64);
    verify(field_rfx->size == sizeof(d64));
    verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_d64));
    verify(string_equal(field_rfx->name, &s("value_d64")));
    verify(field_rfx->index == 0);


  success();
}
