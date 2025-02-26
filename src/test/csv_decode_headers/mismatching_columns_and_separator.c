test( csv_decode_headers, mismatching_columns_and_separator ) {

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


  when("the file has columns count that do not match the separator");
    csv_file =
      "first col;second col;third col;fourth col;fifth col"   "\n"
      "0;1;2;3;4"                                             "\n"
      "0;1;2;3;4"                                             "\n"
      "0;1;2;3;4"                                             "\n";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_reader(csv_file, strlen(csv_file));
    struct map* headers = csv_decode_headers(&input, &fields, &allocator, csv);


  must("fail to decode the headers");
    verify(error.occurred == true);
    verify(headers == NULL);
    verify(streq(error.message,
      "expected a csv with 7 columns, but found only 4 separators `;`"));


  success();
    memory_release(&allocator);
}
