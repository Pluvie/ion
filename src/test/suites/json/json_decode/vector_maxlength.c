test( json_decode, vector_maxlength ) {

  given("an example vector");
    struct vector users;

    struct user {
      char* name;
      u32 age;
    };


  when("it has an associated reflection that enforces a maximum length");
    struct reflection rfx = {
      type(VECTOR), limited_to(0, 2), of({
        type(STRUCT, struct user), fields({
          { field(name, POINTER, struct user), of({ type(CHAR) }) },
          { field(age, U64, struct user) },
        })
      })
    };


  when("some input data is ready to decode, and the max length is not satisfied");
    char* input =
      " ["
      "   { \"name\": \"Augustine\", \"age\": 25 },"
      "   { \"name\": \"Tess Gold\", \"age\": 19 },"
      "   { \"name\": \"Donadel\", \"age\": 60 }"
      " ]";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    json_decode(&users, &source, &rfx, &allocator);


  must("fail to decode the input data and report the error properly");
    char* expected_error =
      "vector required maximum length of 2, at position 115:\n"
      "adel\", \"age\": 60 } ]\n"
      "                   ^";
    verify(error.occurred == true);
    verify(streq(expected_error, error.message));


  success();
    memory_release(&allocator);
}
