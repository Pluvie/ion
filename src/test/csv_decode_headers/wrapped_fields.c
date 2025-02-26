test( csv_decode_headers, wrapped_fields ) {

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
      "'first col';'second col';'third col';'fourth col';'fifth col'"   "\n"
      "'0';'1';'2';'3';'4'"                                             "\n"
      "'0';'1';'2';'3';'4'"                                             "\n"
      "'0';'1';'2';'3';'4'"                                             "\n";


  calling("csv_decode_headers()");
    struct memory allocator = memory_init(0);
    struct io input = io_reader(csv_file, strlen(csv_file));
    struct map* headers = csv_decode_headers(&input, &fields, &allocator, csv);


  must("decode the headers correctly");
    verify(error.occurred == false);
    verify(headers != NULL);
    verify(headers->length == 5);

    struct csv_header* header;
    header = map_get(headers, &(u64) { 0 });
    verify(header != NULL);
    verify(strneq("first col", header->name->content, header->name->length));

    header = map_get(headers, &(u64) { 1 });
    verify(header != NULL);
    verify(strneq("second col", header->name->content, header->name->length));

    header = map_get(headers, &(u64) { 2 });
    verify(header != NULL);
    verify(strneq("third col", header->name->content, header->name->length));

    header = map_get(headers, &(u64) { 3 });
    verify(header != NULL);
    verify(strneq("fourth col", header->name->content, header->name->length));

    header = map_get(headers, &(u64) { 4 });
    verify(header != NULL);
    verify(strneq("fifth col", header->name->content, header->name->length));


  success();
    memory_release(&allocator);
}
