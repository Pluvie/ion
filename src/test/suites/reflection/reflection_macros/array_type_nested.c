test( reflection_macros, array_type_nested ) {

  given("an array");
    struct array x_axis;
    struct array y_axis;
    struct array z_axis;

    struct space {
      d64 temperature;
      d64 humidity;
    };


  calling("the reflection macros");
    struct reflection rfx = {
      type(ARRAY), of({
        type(ARRAY), of({
          type(ARRAY), of({
            type(STRUCT, struct space), fields({
              { field(temperature, D64, struct space) },
              { field(humidity, D64, struct space) },
            }),
          }),
        }),
      }),
    };


  must("correctly define the reflection");
    verify(rfx.type == ARRAY);
    verify(rfx.size == sizeof(x_axis));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.name == NULL);
    verify(rfx.element != NULL);

    struct reflection* element_rfx = rfx.element;
    verify(element_rfx->type == ARRAY);
    verify(element_rfx->size == sizeof(y_axis));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->element != NULL);

    element_rfx = element_rfx->element;
    verify(element_rfx->type == ARRAY);
    verify(element_rfx->size == sizeof(z_axis));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->element != NULL);

    element_rfx = element_rfx->element;
    verify(element_rfx->type == STRUCT);
    verify(element_rfx->size == sizeof(struct space));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->fields != NULL);
    verify(element_rfx->fields->length == 2);

    struct reflection* field_rfx;
    field_rfx = vector_get(element_rfx->fields, 0);
    verify(field_rfx->type == D64);
    verify(field_rfx->size == sizeof(d64));
    verify(field_rfx->offset == offsetof(struct space, temperature));
    verify(streq(field_rfx->name->content, "temperature"));
    verify(field_rfx->index == 0);

    field_rfx = vector_get(element_rfx->fields, 1);
    verify(field_rfx->type == D64);
    verify(field_rfx->size == sizeof(d64));
    verify(field_rfx->offset == offsetof(struct space, humidity));
    verify(streq(field_rfx->name->content, "humidity"));
    verify(field_rfx->index == 0);


  success();
}
