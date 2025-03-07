test( json_decode, struct ) {

  given("an example struct");
    struct example {
      u8 number;
      char* string;
      struct array points;
    } example;

    struct point {
      d64 x;
      d64 y;
    };


  when("it has an associated reflection");
    struct reflect reflection = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, number), type(U8) },
        { field(struct example, string), type(POINTER), of({ type(CHAR) }) },
        { field(struct example, points), type(ARRAY, 0, 0), of({
            type(STRUCT, sizeof(struct point)), fields({
              { field(struct point, x), type(D64) },
              { field(struct point, y), type(D64) },
            })
          })
        },
      })
    };


  when("some input data is ready to decode");
    char* input =
      " {"
      "   \"number\": 255,"
      "   \"ignored_field\": \"ignore me\","
      "   \"string\": \"example\","
      "   \"points\": ["
      "     { \"x\": 3.14, \"y\": 7 },"
      "     { \"x\": 5.05, \"y\": -9 }"
      "   ],"
      "   \"empty_array\": []"
      " }";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_memory(input, strlen(input));
    struct object target = object(example, &reflection, &allocator);
    json_decode(&source, &target);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(example.number == 255);
    verify(streq("example", example.string));

    struct point* point;
    point = array_get(&(example.points), 0);
    verify(point->x == 3.14);
    verify(point->y == 7.0);
    point = array_get(&(example.points), 1);
    verify(point->x == 5.05);
    verify(point->y == -9.0);


  success();
    memory_release(&allocator);
}
