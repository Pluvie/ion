test( csv_decode_headers, wrapped_fields_incorrect ) {

  given("a csv file");
    char* csv_file;
    struct csv_properties csv = {
      .separator = ';',
      .wrapper = '\'',
      .columns_count = 5,
      .encoding = UTF_8,
    };


  when("it has an associated reflection");
    struct vector fields = vector_of(struct reflect, {
      { type(I32), .name = "first col" },
      { type(I32), .name = "second col" },
      { type(I32), .name = "third col" },
      { type(I32), .name = "fourth col" },
      { type(I32), .name = "fifth col" },
    });


  when("the file has columns count that match the separator with a field wrapper");
    csv_file =
      "'first col';'second col';third col;'fourth col';'fifth col'"     "\n"
      "'0';'1';'2';'3';'4'"                                             "\n"
      "'0';'1';'2';'3';'4'"                                             "\n"
      "'0';'1';'2';'3';'4'"                                             "\n";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_reader(csv_file, strlen(csv_file));
    struct map* headers = csv_decode_headers(&input, &fields, &allocator, csv);


  must("fail to decode the headers");
    char* expected_error =
      "expected field to be wrapped with `'`, at position 26:\n"
      " col';'second col';third col;'fourth col\n"
      "                   ^";
    verify(error.occurred == true);
    verify(headers == NULL);
    verify(streq(error.message, expected_error));


  success();
    memory_release(&allocator);
}
