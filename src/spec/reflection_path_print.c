spec( reflection_path_print ) {

  argument(struct reflection* rfx);
  argument(char* result);
  argument(int length);

  precondition("a valid reflection");
  precondition("a valid result");
  precondition("a valid maximum result length");
    #define preconditions \
      char result_holder[256] = { 0 }; \
      result = result_holder; \
      length = sizeof(result_holder);

  when("a supposed error is found in a struct field") {
    apply(preconditions);

    rfx = list_at(rfx_blueprint.fields, 0);
    reflection_path_print(rfx, result, length);

    must("print the field name");
      verify(streq(rfx->name, result));

  } end();

  when("a supposed error is found in a nested struct field") {
    apply(preconditions);

    struct reflection* field = reflection_field_find(&rfx_blueprint, s("v_struct"));
    rfx = reflection_field_find(field, s("v_int"));
    reflection_path_print(rfx, result, length);

    must("print the dot separated field path");
      verify(streq("v_struct.v_int", result));

  } end();

  when("a supposed error is found in a struct field of type array") {
    apply(preconditions);

    struct reflection* field = reflection_field_find(&rfx_blueprint, s("v_array"));
    rfx = field->element;
    rfx->parent = field;
    rfx->index = 7;
    reflection_path_print(rfx, result, length);

    must("print the field name with index");
      verify(streq("v_array.7", result));

  } end();

  #undef preconditions
}
