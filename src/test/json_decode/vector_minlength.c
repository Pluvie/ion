test( json_decode, vector_minlength ) {

  given("an example vector");
    struct vector users;

    struct user {
      char* name;
      u32 age;
    };


  when("it has an associated reflection that enforces a minimum length");
    struct reflect reflection = {
      type(VECTOR, 2, 0), of({
        type(STRUCT, sizeof(struct user)), fields({
          { field(struct user, name), type(POINTER), of({ type(CHAR) }) },
          { field(struct user, age), type(U64) },
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
    struct io source = io_memory(input, strlen(input));
    struct object target = object(users, &reflection, &allocator);
    json_decode(&source, &target);


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
