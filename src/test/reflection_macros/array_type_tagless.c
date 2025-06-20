test( reflection_macros, array_type_tagless ) {

  given("a struct");
    struct example {
      int value_int;
      struct {
        int value_int;
        dec value_dec;
      } why[3];
    };


  calling("the reflection macros");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(value_int, INT, struct example) },
        { field(why, ARRAY, struct example), of({
            type(STRUCT, typeof(*o(struct example)->why)), fields({
              { field(value_int, INT, typeof(*o(struct example)->why)) },
              { field(value_dec, DEC, typeof(*o(struct example)->why)) },
            })
          })
        },
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
    verify(field_rfx->type == ARRAY);
    verify(streq(field_rfx->name, "why"));
    verify(streq(field_rfx->type_name, "struct example"));
    verify(field_rfx->size == sizeof(o(struct example)->why));
    verify(field_rfx->offset == offsetof(struct example, why));
    verify(field_rfx->index == 0);
    verify(field_rfx->element != NULL);

    struct reflection* element_rfx;
    element_rfx = field_rfx->element;
    verify(element_rfx->type == STRUCT);
    verify(strnull(element_rfx->name));
    verify(streq(element_rfx->type_name, "typeof(*((struct example*) 0)->why)"));
    verify(element_rfx->size == sizeof(*o(struct example)->why));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->fields != NULL);
    verify(element_rfx->fields->length == 2);

    field_rfx = list_at(element_rfx->fields, 0);
    verify(field_rfx->type == INT);
    verify(streq(field_rfx->name, "value_int"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(int));
    verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_int));
    verify(field_rfx->index == 0);

    field_rfx = list_at(element_rfx->fields, 1);
    verify(field_rfx->type == DEC);
    verify(streq(field_rfx->name, "value_dec"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(dec));
    verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_dec));
    verify(field_rfx->index == 0);


  success();
}
