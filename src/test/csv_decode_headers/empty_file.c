test( csv_decode_headers, empty_file ) {

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


  when("the file is empty");
    csv_file = "";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_memory(csv_file, strlen(csv_file));
    struct map* headers = csv_decode_headers(&input, &fields, &allocator, csv);


  must("fail to decode the headers");
    verify(error.occurred == true);
    verify(headers == NULL);
    verify(streq(error.message, "csv is empty"));


  success();
    memory_release(&allocator);
}
