test( reflection_macros, struct_type_define ) {

  given("a struct");
    struct example {
      int value_int;
      dec value_dec;
      struct {
        char* text;
        int number;
        struct {
          char* text;
          int number;
        } inside_2;
      } inside_1;
    };


  calling("the reflection macros using a definition to avoid repeating the type");
    #define t struct example
    struct reflection rfx = {
      type(STRUCT, t), fields({
        { field(value_int, INT, t) },
        { field(value_dec, DEC, t) },
        { field(inside_1, STRUCT, t), fields({
            { field(text, POINTER, t, inside_1), of({ type(CHAR) }) },
            { field(number, INT, t, inside_1) },
            { field(inside_2, STRUCT, t, inside_1), fields({
                { field(text, POINTER, t, inside_1.inside_2), of({ type(CHAR) }) },
                { field(number, INT, t, inside_1.inside_2) },
              })
            },
          })
        },
      }),
    };
    #undef t


  must("correctly define the reflection");
    verify(rfx.type == STRUCT);
    verify(strnull(rfx.name));
    verify(streq(rfx.type_name, "struct example"));
    verify(rfx.size == sizeof(struct example));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.fields != NULL);
    verify(rfx.fields->length == 3);

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

    struct example example;
    struct reflection* inside_1_rfx = list_at(rfx.fields, 2);
    verify(inside_1_rfx->type == STRUCT);
    verify(streq(inside_1_rfx->name, "inside_1"));
    verify(strnull(inside_1_rfx->type_name));
    verify(inside_1_rfx->size == sizeof(example.inside_1));
    verify(inside_1_rfx->offset == offsetof(struct example, inside_1));
    verify(inside_1_rfx->index == 0);
    verify(inside_1_rfx->fields != NULL);
    verify(inside_1_rfx->fields->length == 3);

    field_rfx = list_at(inside_1_rfx->fields, 0);
    verify(field_rfx->type == POINTER);
    verify(streq(field_rfx->name, "text"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(void*));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.text) - offsetof(struct example, inside_1));
    verify(field_rfx->index == 0);

    field_rfx = list_at(inside_1_rfx->fields, 1);
    verify(field_rfx->type == INT);
    verify(streq(field_rfx->name, "number"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(int));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.number) - offsetof(struct example, inside_1));
    verify(field_rfx->index == 0);

    struct reflection* inside_2_rfx = list_at(inside_1_rfx->fields, 2);
    verify(inside_2_rfx->type == STRUCT);
    verify(streq(inside_2_rfx->name, "inside_2"));
    verify(strnull(inside_2_rfx->type_name));
    verify(inside_2_rfx->size == sizeof(example.inside_1.inside_2));
    verify(inside_2_rfx->offset ==
      offsetof(struct example, inside_1.inside_2) - offsetof(struct example, inside_1));
    verify(inside_2_rfx->index == 0);
    verify(inside_2_rfx->fields != NULL);
    verify(inside_2_rfx->fields->length == 2);

    field_rfx = list_at(inside_2_rfx->fields, 0);
    verify(field_rfx->type == POINTER);
    verify(streq(field_rfx->name, "text"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(void*));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.inside_2.text) -
      offsetof(struct example, inside_1.inside_2));
    verify(field_rfx->index == 0);

    field_rfx = list_at(inside_2_rfx->fields, 1);
    verify(field_rfx->type == INT);
    verify(streq(field_rfx->name, "number"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(int));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.inside_2.number) -
      offsetof(struct example, inside_1.inside_2));
    verify(field_rfx->index == 0);


  success();
}
