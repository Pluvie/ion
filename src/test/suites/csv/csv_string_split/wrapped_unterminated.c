test( csv_string_split, wrapped_unterminated ) {

  given("a string");
    struct string string = s("'example';'str;ing';'with';'separators");


  calling("csv_string_split()");
    struct memory allocator = memory_init(0);
    struct array* chunks = csv_string_split(string, &allocator, ';', '\'');


  must("split the string into an array of chunks");
    verify(error.occurred == false);
    verify(chunks != NULL);
    verify(chunks->length == 4);

    struct string* chunk;
    chunk = array_get(chunks, 0);
    verify(strneq(chunk->content, "'example'", chunk->length));
    chunk = array_get(chunks, 1);
    verify(strneq(chunk->content, "'str;ing'", chunk->length));
    chunk = array_get(chunks, 2);
    verify(strneq(chunk->content, "'with'", chunk->length));
    chunk = array_get(chunks, 3);
    verify(strneq(chunk->content, "'separators'", chunk->length));


  success();
    memory_release(&allocator);
}
