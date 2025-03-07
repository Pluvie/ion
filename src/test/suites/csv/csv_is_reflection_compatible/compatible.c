test( csv_is_reflection_compatible, compatible ) {

  given("a csv reflection");
    struct user {
      struct string name;
      u32 age;
    };

    struct reflection rfx = {
      type(ARRAY), of({
        type(STRUCT, struct user), fields({
          { field(name, STRING, struct user), named("USERNAME") },
          { field(age, U32, struct user), named("AGE") },
        })
      })
    };


  calling("csv_is_reflection_compatible()");
    bool compatible = csv_is_reflection_compatible(&rfx);


  must("return true");
    verify(error.occurred == false);
    verify(compatible == true);


  success();
}
