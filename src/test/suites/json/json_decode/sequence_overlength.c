test( json_decode, sequence_overlength ) {

  given("an example sequence");
    struct user {
      char* name;
      u32 age;
    } users[2];


  when("it has an associated reflection");
    struct reflection rfx = {
      type(SEQUENCE, typeof(users)), of({
        type(STRUCT, struct user), fields({
          { field(name, POINTER, struct user), of({ type(CHAR) }) },
          { field(age, U64, struct user) },
        })
      })
    };


  when("some input data is ready to decode");
    char* input =
      " ["
      "   { \"name\": \"Augustine\", \"age\": 25 },"
      "   { \"name\": \"Tess Gold\", \"age\": 19 },"
      "   { \"name\": \"Donadel\", \"age\": 60 }"
      " ]";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    json_decode(users, &source, &rfx, &allocator);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(streq("Augustine", users[0].name));
    verify(users[0].age == 25);
    verify(streq("Tess Gold", users[1].name));
    verify(users[1].age == 19);


  success();
    memory_release(&allocator);
}
