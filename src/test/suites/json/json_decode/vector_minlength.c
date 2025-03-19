test( json_decode, vector_minlength ) {

  given("an example vector");
    struct vector users;

    struct user {
      char* name;
      u32 age;
    };


  when("it has an associated reflection that enforces a minimum length");
    struct reflection rfx = {
      type(VECTOR), limited_to(2, 0), of({
        type(STRUCT, struct user), fields({
          { field(name, POINTER, struct user), of({ type(CHAR) }) },
          { field(age, U64, struct user) },
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
    json_decode(&users, &source, &rfx, &allocator);


  must("fail to decode the input data and report the error properly");
    char* expected_error =
      "vector required minimum length of 2, at position 41:\n"
      "tine\", \"age\": 25 } ]\n"
      "                   ^";
    verify(error.occurred == true);
    verify(streq(expected_error, error.message));


  success();
    memory_release(&allocator);
}
