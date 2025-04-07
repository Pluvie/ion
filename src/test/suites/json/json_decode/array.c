test( json_decode, array ) {

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
      " ["
      "   { \"name\": \"Augustine\", \"age\": 25 },"
      "   { \"name\": \"Tess Gold\", \"age\": 19 }"
      " ]";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    json_decode(&users, &source, &rfx, &allocator);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);

    struct user* user;
    user = array_get(&users, 0);
    verify(string_equal(&s("Augustine"), &(user->name)));
    verify(user->age == 25);
    user = array_get(&users, 1);
    verify(string_equal(&s("Tess Gold"), &(user->name)));
    verify(user->age == 19);


  success();
    memory_release(&allocator);
}
