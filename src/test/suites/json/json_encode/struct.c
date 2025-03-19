test( json_encode, struct ) {

  given("an example struct");
    struct example {
      struct array* users;
      u32 numbers[7];
    } example;


  when("it has an associated reflection");
    #define t struct example
    #define u struct { u32 age; struct string name; }
    struct reflection rfx = {
      type(STRUCT, t), fields({
        { field(users, POINTER, t),
            of({ type(ARRAY), of({
              type(STRUCT, u), fields({
                { field(age, U32, u) },
                { field(name, STRING, u) },
              })
            })
          })
        },
        { field(numbers, SEQUENCE, t), of({ type(U32) }) },
      })
    };
    #undef t
    #undef u


  when("some input data is ready to decode");
    example.users = &array_of(struct { u32 age; struct string name; }, {
      { .age = 17, .name = s("Esculapio") },
      { .age = 33, .name = s("Romualdo") },
    });
    u32 numbers[7] = { 1, 2, 3, 4, 5, 6, 7 };
    memcpy(example.numbers, numbers, sizeof(numbers));


  calling("json_encode()");
    char wire[1024] = { 0 };
    struct io output = io_open_memory(wire, sizeof(wire));
    json_encode(&example, &output, &rfx);


  must("encode the input data on the struct correctly");
    char expected_wire[] =
      "{"
        "\"users\":["
          "{\"age\":17,\"name\":\"Esculapio\"},"
          "{\"age\":33,\"name\":\"Romualdo\"}"
        "],"
        "\"numbers\":["
          "1,"
          "2,"
          "3,"
          "4,"
          "5,"
          "6,"
          "7"
        "]"
      "}";

    verify(error.occurred == false);
    verify(memeq(wire, expected_wire, sizeof(expected_wire)) == true);


  success();
}
