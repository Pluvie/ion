test( reflection_macros, list_type_limited ) {

  given("a list");
    list<struct squadmate> squad;


  calling("the reflection macros with size limits");
    struct reflection rfx = {
      type(LIST), limited_to(4, 8), of({
        type(STRUCT, struct squadmate), fields({
          { field(name, STRING, struct squadmate) },
          { field(class, ENUM, struct squadmate) },
          { field(health, INT, struct squadmate) },
          { field(shields, INT, struct squadmate) },
        }),
      }),
    };


  must("correctly define the reflection");
    verify(rfx.type == LIST);
    verify(strnull(rfx.name));
    verify(strnull(rfx.type_name));
    verify(rfx.size == sizeof(squad));
    verify(rfx.size_limits.min == 4);
    verify(rfx.size_limits.max == 8);
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.element != NULL);

    struct reflection* element_rfx = rfx.element;
    verify(element_rfx->type == STRUCT);
    verify(strnull(element_rfx->name));
    verify(streq(element_rfx->type_name, "struct squadmate"));
    verify(element_rfx->size == sizeof(struct squadmate));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->fields != NULL);
    verify(element_rfx->fields->length == 4);

    struct reflection* field_rfx;
    field_rfx = list_at(element_rfx->fields, 0);
    verify(field_rfx->type == STRING);
    verify(streq(field_rfx->name, "name"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(struct string));
    verify(field_rfx->offset == offsetof(struct squadmate, name));
    verify(field_rfx->index == 0);

    field_rfx = list_at(element_rfx->fields, 1);
    verify(field_rfx->type == ENUM);
    verify(streq(field_rfx->name, "class"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(enum classes));
    verify(field_rfx->offset == offsetof(struct squadmate, class));
    verify(field_rfx->index == 0);

    field_rfx = list_at(element_rfx->fields, 2);
    verify(field_rfx->type == INT);
    verify(streq(field_rfx->name, "health"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(int));
    verify(field_rfx->offset == offsetof(struct squadmate, health));
    verify(field_rfx->index == 0);

    field_rfx = list_at(element_rfx->fields, 3);
    verify(field_rfx->type == INT);
    verify(streq(field_rfx->name, "shields"));
    verify(strnull(field_rfx->type_name));
    verify(field_rfx->size == sizeof(int));
    verify(field_rfx->offset == offsetof(struct squadmate, shields));
    verify(field_rfx->index == 0);


  success();
}
