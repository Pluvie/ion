test( json_decode, array_empty ) {

  given("an example array");
    struct array users;

    struct user {
      struct string name;
      u32 age;
    };


  when("it has an associated reflection");
    struct reflection rfx = {
      type(ARRAY), of({
        type(STRUCT, struct user), fields({
          { field(name, STRING, struct user) },
          { field(age, U32, struct user) },
        })
      })
    };


  when("some input data is ready to decode");
    char* input =
      "[ ]";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    reflection_initialize(&rfx, &users, &allocator);
    json_decode(&source, &rfx);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(users.length == 0);
    verify(users.data != NULL);


  success();
    memory_release(&allocator);
}
