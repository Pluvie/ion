test( csv_is_reflection_compatible, incompatible_struct_fields ) {

  given("a csv reflection");
    struct user {
      char* name;
      u32 age;
    };

    struct reflection rfx = {
      type(ARRAY), of({
        type(STRUCT, struct user), fields({
          { field(name, POINTER, struct user), of({ type(CHAR) }), named("USERNAME") },
          { field(age, U32, struct user), named("AGE") },
        })
      })
    };


  calling("csv_is_reflection_compatible()");
    bool compatible = csv_is_reflection_compatible(&rfx);


  must("return false");
    verify(error.occurred == true);
    verify(compatible == false);
    verify(streq(error.message,
      "unable to decode csv due to incompatible reflection: all fields of "
      "the struct must be numbers (I32, D64, U64, ecc.), BOOL, or STRING"));


  success();
}
