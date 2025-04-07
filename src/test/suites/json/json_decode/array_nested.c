test( json_decode, array_nested ) {

  given("an example array");
    struct array users;

    struct user {
      struct string* name;
      u32 age;
      struct array* roles;
    };


  when("it has an associated reflection");
    struct reflection rfx = {
      type(ARRAY), of({
        type(STRUCT, struct user), fields({
          { field(name, POINTER, struct user), of({ type(STRING) }) },
          { field(age, U32, struct user) },
          { field(roles, POINTER, struct user), of({
              type(ARRAY), of({ type(STRING) })
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
    struct io source = io_open_memory(input, strlen(input));
    json_decode(&users, &source, &rfx, &allocator);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);

    struct user* user;
    struct string* role;

    user = array_get(&users, 0);
    verify(string_equal(&s("Augustine"), user->name));
    verify(user->age == 25);
    role = array_get(user->roles, 0);
    verify(string_equal(&s("one"), role));
    role = array_get(user->roles, 1);
    verify(string_equal(&s("two"), role));

    user = array_get(&users, 1);
    verify(string_equal(&s("Tess Gold"), user->name));
    verify(user->age == 19);
    role = array_get(user->roles, 0);
    verify(string_equal(&s("three"), role));
    role = array_get(user->roles, 1);
    verify(string_equal(&s("four"), role));


  success();
    memory_release(&allocator);
}
