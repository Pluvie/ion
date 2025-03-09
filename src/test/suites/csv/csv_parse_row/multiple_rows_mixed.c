test( csv_parse_row, multiple_rows_mixed ) {

  given("multiple csv rows with mixed wrappers");
    char* rows =
      "a\n,sample,row\n"
      "another,\"sample\",row\n"
      "\"yet ano,ther\",sample,row\n"
      "and finally,\",last,\",one\n";


  when("the csv properties have the comma as separator");
    struct csv_properties csv = {
      .separator = ',',
      .wrapper = '"',
      .columns_count = 3,
      .encoding = UTF_8,
    };


  calling("csv_parse_row() in succession");
    struct memory allocator = memory_init(0);
    struct io rows_io = io_open_memory(rows, strlen(rows));
    struct array* fields_1 = csv_parse_row(&rows_io, &allocator, csv);
    struct array* fields_2 = csv_parse_row(&rows_io, &allocator, csv);
    struct array* fields_3 = csv_parse_row(&rows_io, &allocator, csv);
    struct array* fields_4 = csv_parse_row(&rows_io, &allocator, csv);


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
        verify(streq("a\n", field->content));
        continue;
      case 1:
        verify(streq("sample", field->content));
        continue;
      case 2:
        verify(streq("row", field->content));
        continue;
      default:
        continue;
      }

    for array_each(fields_2, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(streq("another", field->content));
        continue;
      case 1:
        verify(streq("sample", field->content));
        continue;
      case 2:
        verify(streq("row", field->content));
        continue;
      default:
        continue;
      }

    for array_each(fields_3, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(streq("yet ano,ther", field->content));
        continue;
      case 1:
        verify(streq("sample", field->content));
        continue;
      case 2:
        verify(streq("row", field->content));
        continue;
      default:
        continue;
      }

    for array_each(fields_4, struct string*, field, field_index)
      switch (field_index) {
      case 0:
        verify(streq("and finally", field->content));
        continue;
      case 1:
        verify(streq(",last,", field->content));
        continue;
      case 2:
        verify(streq("one", field->content));
        continue;
      default:
        continue;
      }


  success();
    memory_release(&allocator);
}
