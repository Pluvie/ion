test( json_decode, null_value ) {

  given("an example struct");
    struct example {
      u64 example_u64;
      d64 example_d64;
      struct {
        bool example_bool;
        char* example_string;
        struct {
          u32 number;
          bool example;
        } inner_inner;
      } inner;
      struct {
        struct array* ignored_values;
      } nullable;
      struct string example_string;
    } example;


  when("it has an associated reflection");
    #define t struct example
    struct reflection rfx = {
      type(STRUCT, t), fields({
        { field(example_u64, U64, t) },
        { field(example_d64, D64, t) },
        { field(inner, STRUCT, t), fields({
            { field(example_bool, BOOL, t, inner) },
            { field(example_string, POINTER, t, inner),
                of({ type(CHAR) })
            },
            { field(inner_inner, STRUCT, t, inner), fields({
                { field(number, U32, t, inner.inner_inner) },
                { field(example, BOOL, t, inner.inner_inner) },
              })
            },
          })
        },
        { field(nullable, STRUCT, t), fields({
            { field(ignored_values, POINTER, t, nullable), of({
                type(ARRAY), of({ type(I64) })
               })
            },
          })
        },
        { field(example_string, STRING, t) },
      })
    };
    #undef t


  when("some input data is ready to decode");
    char* input =
      " {"
      "   \"nullable\": null,"
      "   \"example_u64\": null,"
      "   \"example_d64\": null,"
      "   \"inner\": {"
      "     \"example_bool\": null,"
      "     \"inner_inner\": null,"
      "     \"example_string\": null"
      "   },"
      "   \"example_string\": null"
      " }";


  calling("json_decode()");
    struct memory allocator = memory_init(4096);
    struct io source = io_open_memory(input, strlen(input));
    json_decode(&example, &source, &rfx, &allocator);


  must("decode the input data on the struct correctly");
    struct example empty = { 0 };

    verify(error.occurred == false);
    verify(example.example_u64 == 0);
    verify(example.example_d64 == 0.0);
    verify(example.example_string.content == NULL);
    verify(example.example_string.length == 0);
    verify(example.nullable.ignored_values == NULL);
    verify(example.inner.example_bool == false);
    verify(example.inner.example_string == NULL);

    verify(memeq(
      &(example.nullable),
      &(empty.nullable),
      sizeof(example.nullable)));

    verify(memeq(
      &(example.inner.inner_inner),
      &(empty.inner.inner_inner),
      sizeof(example.inner.inner_inner)));


  success();
    memory_release(&allocator);
}
