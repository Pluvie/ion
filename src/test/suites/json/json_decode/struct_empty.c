test( json_decode, struct_empty ) {

  given("an example struct");
    struct example {
      u8 number;
      char* string;
      struct array points;
    } example = { 0 };

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
      "{}";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    reflection_initialize(&rfx, &example, &allocator);
    json_decode(&source, &rfx);


  must("decode the input data on the struct correctly");
    verify(error.occurred == false);
    verify(example.number == 0);
    verify(example.string == NULL);
    verify(example.points.length == 0);
    verify(example.points.data == NULL);


  success();
    memory_release(&allocator);
}
