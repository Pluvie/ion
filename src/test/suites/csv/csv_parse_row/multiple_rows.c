test( csv_parse_row, multiple_rows ) {

  given("multiple csv rows");
    char* rows =
      "a,sample,row\n"
      "another,sample,row\n"
      "yet another,sample,row\n"
      "and finally,last,one\n";


  when("the csv properties have the comma as separator");
    struct csv_properties csv = {
      .separator = ',',
      .wrapper = '\0',
      .columns_count = 3,
      .encoding = UTF_8,
    };


  calling("csv_parse_row() in succession");
    struct memory allocator = memory_init(0);
    struct io rows_io = io_open_memory(rows, strlen(rows));
    struct array* fields_1 = csv_parse_row(&rows_io, &allocator, &csv);
    struct array* fields_2 = csv_parse_row(&rows_io, &allocator, &csv);
    struct array* fields_3 = csv_parse_row(&rows_io, &allocator, &csv);
    struct array* fields_4 = csv_parse_row(&rows_io, &allocator, &csv);


  must("correctly parse the rows into the fields");
    verify(error.occurred == false);
    verify(fields_1 != NULL);
    verify(fields_2 != NULL);
    verify(fields_3 != NULL);
    verify(fields_4 != NULL);
    verify(fields_1->length == csv.columns_count);
    verify(fields_2->length == csv.columns_count);
    verify(fields_3->length == csv.columns_count);
    verify(fields_4->length == csv.columns_count);

    for array_each(fields_1, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(string_equal(field, &s("a")));
        continue;
      case 1:
        verify(string_equal(field, &s("sample")));
        continue;
      case 2:
        verify(string_equal(field, &s("row")));
        continue;
      default:
        continue;
      }

    for array_each(fields_2, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(string_equal(field, &s("another")));
        continue;
      case 1:
        verify(string_equal(field, &s("sample")));
        continue;
      case 2:
        verify(string_equal(field, &s("row")));
        continue;
      default:
        continue;
      }

    for array_each(fields_3, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(string_equal(field, &s("yet another")));
        continue;
      case 1:
        verify(string_equal(field, &s("sample")));
        continue;
      case 2:
        verify(string_equal(field, &s("row")));
        continue;
      default:
        continue;
      }

    for array_each(fields_4, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(string_equal(field, &s("and finally")));
        continue;
      case 1:
        verify(string_equal(field, &s("last")));
        continue;
      case 2:
        verify(string_equal(field, &s("one")));
        continue;
      default:
        continue;
      }


  success();
    memory_release(&allocator);
}
