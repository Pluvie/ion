test( csv_decode_headers, wrapped_fields ) {

  given("a csv file");
    char* csv_file;
    struct csv_properties csv = {
      .separator = ';',
      .wrapper = '\'',
      .columns_count = 5,
      .encoding = UTF_8,
    };


  when("the file has columns count that match the separator with a field wrapper");
    csv_file =
      "'first col';'second col';'third col';'fourth col';'fifth col'"   "\n"
      "'0';'1';'2';'3';'4'"                                             "\n"
      "'0';'1';'2';'3';'4'"                                             "\n"
      "'0';'1';'2';'3';'4'"                                             "\n";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_reader(csv_file, strlen(csv_file));
    struct vector* headers = csv_decode_headers(&input, &allocator, csv);


  must("decode the headers correctly");
    verify(error.occurred == false);
    verify(headers != NULL);
    verify(streq("first col", vector_get(headers, 0)));
    verify(streq("second col", vector_get(headers, 1)));
    verify(streq("third col", vector_get(headers, 2)));
    verify(streq("fourth col", vector_get(headers, 3)));
    verify(streq("fifth col", vector_get(headers, 4)));


  success();
    memory_release(&allocator);
}
