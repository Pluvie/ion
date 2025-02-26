test( csv_decode_headers, no_columns ) {

  given("a csv file");
    char* csv_file;
    struct csv_properties csv = {
      .separator = ';',
      .wrapper = 0,
      .columns_count = 7,
      .encoding = UTF_8,
    };


  when("it has an associated reflection");
    struct vector fields = vector_of(struct reflect, {
      { type(I32), .name = "second col" },
      { type(I32), .name = "fifth col" },
    });


  when("the file has no columns in the header row");
    csv_file = "\n"
      "abc;def\n";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_reader(csv_file, strlen(csv_file));
    struct map* headers = csv_decode_headers(&input, &fields, &allocator, csv);


  must("fail to decode the headers");
    verify(error.occurred == true);
    verify(headers == NULL);
    verify(streq(error.message, "expected a csv with at least one header column"));


  success();
    memory_release(&allocator);
}
