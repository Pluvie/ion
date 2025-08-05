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

  when("a supposed error is found in a top level element") {
    apply(preconditions);
    //rfx = &rfx_blueprint;
    //int result_length = reflection_path_print(rfx, result, length);

    rfx = list_at(rfx_blueprint.fields, 0);
    int result_length = reflection_path_print(rfx, result, length);

    must("print something");
      print("----->\n%.*s", (int32) result_length, result);

  } end();

  #undef preconditions
}
