test( csv_is_reflection_compatible, not_array_of_struct ) {

  given("a csv reflection");
    struct user {
      struct string name;
      u32 age;
    };

    struct reflection rfx = {
      type(ARRAY), of({
        type(ARRAY), of({
          type(STRUCT, struct user), fields({
            { field(name, STRING, struct user), named("USERNAME") },
            { field(age, U32, struct user), named("AGE") },
          })
        })
      })
    };


  calling("csv_is_reflection_compatible()");
    bool compatible = csv_is_reflection_compatible(&rfx);


  must("return false");
    verify(error.occurred == true);
    verify(compatible == false);
    verify(streq(error.message,
      "unable to decode csv due to incompatible reflection: it must be an "
      "ARRAY of type STRUCT"));


  success();
}
