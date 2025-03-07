test( reflection_initialize, deep_propagation ) {

  given("a type");
    struct example {
      u64 value_u64;
      d64 value_d64;
      struct {
        d32 value_d32;
        i32 value_i32;
      } inner;
      struct array* array;
    };


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(value_u64, U64, struct example) },
        { field(value_d64, D64, struct example) },
        { field(inner, STRUCT, struct example), fields({
            { field(value_d32, D32, struct example, inner) },
            { field(value_i32, I32, struct example, inner) },
          }),
        },
        { field(array, POINTER, struct example), of({
            type(ARRAY), of({ type(I16) })
          })
        },
      }),
    };


  when("exists an object of that type");
    struct example object;


  when("an allocator is initialized");
    struct memory allocator = memory_init(0);


  calling("reflection_initialize()");
    reflection_initialize(&rfx, &object, &allocator);


  must("deep propagate the target and allocator");
    verify(rfx.target = &object);
    verify(rfx.allocator = &allocator);

    struct reflection* field_rfx;
    field_rfx = vector_get(rfx.fields, 0);
    verify(field_rfx->target == (void*) &object + offsetof(struct example, value_u64));
    verify(field_rfx->allocator == &allocator);
    verify(field_rfx->parent == &rfx);

    field_rfx = vector_get(rfx.fields, 1);
    verify(field_rfx->target == (void*) &object + offsetof(struct example, value_d64));
    verify(field_rfx->allocator == &allocator);
    verify(field_rfx->parent == &rfx);

    field_rfx = vector_get(rfx.fields, 2);
    verify(field_rfx->target == (void*) &object + offsetof(struct example, inner));
    verify(field_rfx->allocator == &allocator);
    verify(field_rfx->parent == &rfx);

    field_rfx = vector_get(rfx.fields, 3);
    verify(field_rfx->target == (void*) &object + offsetof(struct example, array));
    verify(field_rfx->allocator == &allocator);
    verify(field_rfx->parent == &rfx);

    struct reflection* inner_field_rfx;
    field_rfx = vector_get(rfx.fields, 2);
    inner_field_rfx = vector_get(field_rfx->fields, 0);
    verify(inner_field_rfx->target == (void*) &object +
      offsetof(struct example, inner.value_d32));
    verify(inner_field_rfx->allocator == &allocator);
    verify(inner_field_rfx->parent == field_rfx);

    inner_field_rfx = vector_get(field_rfx->fields, 1);
    verify(inner_field_rfx->target == (void*) &object +
      offsetof(struct example, inner.value_i32));
    verify(inner_field_rfx->allocator == &allocator);
    verify(inner_field_rfx->parent == field_rfx);

    struct reflection* element_rfx;
    field_rfx = vector_get(rfx.fields, 3);
    element_rfx = field_rfx->element;
    verify(element_rfx->target == (void*) &object + offsetof(struct example, array));
    verify(element_rfx->allocator == &allocator);
    verify(element_rfx->parent == field_rfx);


  success();
}
