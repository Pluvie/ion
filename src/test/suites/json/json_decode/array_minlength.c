test( json_decode, array_minlength ) {

  given("an example array");
    struct array users;

    struct user {
      char* name;
      u32 age;
    };


  when("it has an associated reflection that enforces a minimum length");
    struct reflection rfx = {
      type(ARRAY), limited_to(2, 0), of({
        type(STRUCT, struct user), fields({
          { field(name, POINTER, struct user), of({ type(CHAR) }) },
          { field(age, U32, struct user) },
        })
      })
    };


  when("some input data is ready to decode, and the min length is not satisfied");
    char* input =
      " ["
      "   { \"name\": \"Augustine\", \"age\": 25 }"
      " ]";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    reflection_initialize(&rfx, &users, &allocator);
    json_decode(&source, &rfx);


  must("fail to decode the input data and report the error properly");
    char* expected_error =
      "array required minimum length of 2, at position 41:\n"
      "tine\", \"age\": 25 } ]\n"
      "                   ^";
    verify(error.occurred == true);
    verify(streq(expected_error, error.message));


  success();
    memory_release(&allocator);
}
