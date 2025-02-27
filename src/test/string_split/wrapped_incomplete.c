test( string_split, wrapped_incomplete ) {

  given("a string");
    struct string string = s("'example';'str;ing;'with';'separators'");


  calling("string_split()");
    struct memory allocator = memory_init(0);
    struct array* chunks = string_split(string, &allocator, ';', '\'');


  must("split the string into an array of chunks");
    verify(error.occurred == false);
    verify(chunks != NULL);
    verify(chunks->length == 2);

    struct string* chunk;
    chunk = array_get(chunks, 0);
    verify(strneq(chunk->content, "'example'", chunk->length));
    chunk = array_get(chunks, 1);
    verify(strneq(chunk->content, "'str;ing;'with';'separators'", chunk->length));


  success();
    memory_release(&allocator);
}
