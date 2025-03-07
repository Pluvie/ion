test( reflection_macros, struct_type_defined ) {

  given("a struct");
    struct example {
      u64 value_u64;
      d64 value_d64;
      struct {
        char* string;
        u32 number;
        struct {
          char* string;
          u32 number;
        } inside_2;
      } inside_1;
    };


  calling("the reflection macros using a definition to avoid repeating the type");
    #define t struct example
    struct reflection rfx = {
      type(STRUCT, t), fields({
        { field(value_u64, U64, t) },
        { field(value_d64, D64, t) },
        { field(inside_1, STRUCT, t), fields({
            { field(string, POINTER, t, inside_1),
                of({ type(CHAR) })
            },
            { field(number, U32, t, inside_1) },
            { field(inside_2, STRUCT, t, inside_1), fields({
                { field(string, POINTER, t, inside_1.inside_2),
                    of({ type(CHAR) })
                },
                { field(number, U32, t, inside_1.inside_2) },
              })
            },
          })
        },
      }),
    };
    #undef t


  must("correctly define the reflection");
    verify(rfx.type == STRUCT);
    verify(rfx.size == sizeof(struct example));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.name == NULL);
    verify(rfx.fields != NULL);
    verify(rfx.fields->length == 3);

    struct reflection* field_rfx;
    field_rfx = vector_get(rfx.fields, 0);
    verify(field_rfx->type == U64);
    verify(field_rfx->size == sizeof(u64));
    verify(field_rfx->offset == offsetof(struct example, value_u64));
    verify(streq(field_rfx->name->content, "value_u64"));
    verify(field_rfx->index == 0);

    field_rfx = vector_get(rfx.fields, 1);
    verify(field_rfx->type == D64);
    verify(field_rfx->size == sizeof(d64));
    verify(field_rfx->offset == offsetof(struct example, value_d64));
    verify(streq(field_rfx->name->content, "value_d64"));
    verify(field_rfx->index == 0);

    struct example example;
    struct reflection* inside_1_rfx = vector_get(rfx.fields, 2);
    verify(inside_1_rfx->type == STRUCT);
    verify(inside_1_rfx->size == sizeof(example.inside_1));
    verify(inside_1_rfx->offset == offsetof(struct example, inside_1));
    verify(inside_1_rfx->index == 0);
    verify(streq(inside_1_rfx->name->content, "inside_1"));
    verify(inside_1_rfx->fields != NULL);
    verify(inside_1_rfx->fields->length == 3);

    field_rfx = vector_get(inside_1_rfx->fields, 0);
    verify(field_rfx->type == POINTER);
    verify(field_rfx->size == sizeof(void*));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.string) - offsetof(struct example, inside_1));
    verify(streq(field_rfx->name->content, "string"));
    verify(field_rfx->index == 0);
    verify(field_rfx->element != NULL);
    verify(field_rfx->element->type == CHAR);

    field_rfx = vector_get(inside_1_rfx->fields, 1);
    verify(field_rfx->type == U32);
    verify(field_rfx->size == sizeof(u32));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.number) - offsetof(struct example, inside_1));
    verify(streq(field_rfx->name->content, "number"));
    verify(field_rfx->index == 0);

    struct reflection* inside_2_rfx = vector_get(inside_1_rfx->fields, 2);
    verify(inside_2_rfx->type == STRUCT);
    verify(inside_2_rfx->size == sizeof(example.inside_1.inside_2));
    verify(inside_2_rfx->offset ==
      offsetof(struct example, inside_1.inside_2) - offsetof(struct example, inside_1));
    verify(inside_2_rfx->index == 0);
    verify(streq(inside_2_rfx->name->content, "inside_2"));
    verify(inside_2_rfx->fields != NULL);
    verify(inside_2_rfx->fields->length == 2);

    field_rfx = vector_get(inside_2_rfx->fields, 0);
    verify(field_rfx->type == POINTER);
    verify(field_rfx->size == sizeof(void*));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.inside_2.string) -
      offsetof(struct example, inside_1.inside_2));
    verify(streq(field_rfx->name->content, "string"));
    verify(field_rfx->index == 0);
    verify(field_rfx->element != NULL);
    verify(field_rfx->element->type == CHAR);

    field_rfx = vector_get(inside_2_rfx->fields, 1);
    verify(field_rfx->type == U32);
    verify(field_rfx->size == sizeof(u32));
    verify(field_rfx->offset ==
      offsetof(struct example, inside_1.inside_2.number) -
      offsetof(struct example, inside_1.inside_2));
    verify(streq(field_rfx->name->content, "number"));
    verify(field_rfx->index == 0);


  success();
}
