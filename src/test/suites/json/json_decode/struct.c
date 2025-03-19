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
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(number, U8, struct example) },
        { field(string, POINTER, struct example), of({ type(CHAR) }) },
        { field(points, ARRAY, struct example), of({
            type(STRUCT, struct point), fields({
              { field(x, D64, struct point) },
              { field(y, D64, struct point) },
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
    struct io source = io_open_memory(input, strlen(input));
    json_decode(&example, &source, &rfx, &allocator);


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
