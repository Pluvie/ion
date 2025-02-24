test( json_decode, array_nested ) {
  print("");

  given("an example array");
    struct data {
      struct array* users;
    };

    struct user {
      char* name;
      u32 age;
      struct array* roles;
    };


  when("it has an associated reflection");
    struct reflect reflection = {
      type(ARRAY, 0, 0), of({
        type(STRUCT, sizeof(struct user)), fields({
          { field(struct user, name), type(POINTER), of({ type(CHAR) }) },
          { field(struct user, age), type(U32) },
          { field(struct user, roles), type(POINTER), of({
              type(ARRAY, 0, 0), of({ type(POINTER), of({ type(CHAR) }) })
            })
          },
        })
      })
    };


  when("some input data is ready to decode");
    char* input =
      " ["
      "   { \"name\": \"Augustine\", \"age\": 25, \"roles\": [ \"one\", \"two\" ] },"
      "   { \"name\": \"Tess Gold\", \"age\": 19, \"roles\": [ \"three\", \"four\" ] }"
      " ]";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_reader(input, strlen(input));
    struct object target = object(users, &reflection, &allocator);
    json_decode(&source, &target);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);

    struct user* user;
    user = array_get(&users, 0);
    verify(streq("Augustine", user->name));
    verify(user->age == 25);
    verify(streq("one", *(char**) array_get(user->roles, 0)));
    verify(streq("two", *(char**) array_get(user->roles, 1)));
    user = array_get(&users, 1);
    verify(streq("Tess Gold", user->name));
    verify(user->age == 19);
    verify(streq("three", *(char**) array_get(user->roles, 0)));
    verify(streq("four", *(char**) array_get(user->roles, 1)));


  success();
    memory_release(&allocator);
}
