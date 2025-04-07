test( reflection_macros, array_type_limited ) {

  given("an array");
    struct array countries;

    struct {
      struct string name;
      u64 population;
    } country;


  calling("the reflection macros with size limits");
    struct reflection rfx = {
      type(ARRAY), limited_to(4, 8), of({
        type(STRUCT, typeof(country)), fields({
          { field(name, STRING, typeof(country)) },
          { field(population, U64, typeof(country)) },
        }),
      }),
    };


  must("correctly define the reflection");
    verify(rfx.type == ARRAY);
    verify(rfx.size == sizeof(countries));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.name == NULL);
    verify(rfx.size_limits.min == 4);
    verify(rfx.size_limits.max == 8);
    verify(rfx.element != NULL);

    struct reflection* element_rfx = rfx.element;
    verify(element_rfx->type == STRUCT);
    verify(element_rfx->size == sizeof(typeof(country)));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->fields != NULL);
    verify(element_rfx->fields->length == 2);

    struct reflection* field_rfx;
    field_rfx = vector_get(element_rfx->fields, 0);
    verify(field_rfx->type == STRING);
    verify(field_rfx->size == sizeof(struct string));
    verify(field_rfx->offset == offsetof(typeof(country), name));
    verify(string_equal(field_rfx->name, &s("name")));
    verify(field_rfx->index == 0);

    field_rfx = vector_get(element_rfx->fields, 1);
    verify(field_rfx->type == U64);
    verify(field_rfx->size == sizeof(u64));
    verify(field_rfx->offset == offsetof(typeof(country), population));
    verify(string_equal(field_rfx->name, &s("population")));
    verify(field_rfx->index == 0);


  success();
}
