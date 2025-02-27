test( json_decode, sequence ) {

  given("an example sequence");
    struct user {
      char* name;
      u32 age;
    } users[4];


  when("it has an associated reflection");
    struct reflect reflection = {
      type(SEQUENCE, 4), of({
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
    verify(streq("Augustine", users[0].name));
    verify(users[0].age == 25);
    verify(streq("Tess Gold", users[1].name));
    verify(users[1].age == 19);


  success();
    memory_release(&allocator);
}
