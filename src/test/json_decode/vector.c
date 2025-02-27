test( json_decode, vector ) {

  given("an example vector");
    struct vector users;

    struct user {
      char* name;
      u32 age;
    };


  when("it has an associated reflection");
    struct reflect reflection = {
      type(VECTOR, 0, 0), of({
        type(STRUCT, sizeof(struct user)), fields({
          { field(struct user, name), type(POINTER), of({ type(CHAR) }) },
          { field(struct user, age), type(U64) },
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
    struct io source = io_memory(input, strlen(input));
    struct object target = object(users, &reflection, &allocator);
    json_decode(&source, &target);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);

    struct user* user;
    user = vector_get(&users, 0);
    verify(streq("Augustine", user->name));
    verify(user->age == 25);
    user = vector_get(&users, 1);
    verify(streq("Tess Gold", user->name));
    verify(user->age == 19);


  success();
    memory_release(&allocator);
}
