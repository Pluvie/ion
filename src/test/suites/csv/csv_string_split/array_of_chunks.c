test( csv_string_split, array_of_chunks ) {

  given("a string");
    struct string string = s("example;string;with;separators\n");


  calling("csv_string_split()");
    struct memory allocator = memory_init(0);
    struct array* chunks = csv_string_split(string, &allocator, ';', 0);


  must("split the string into an array of chunks");
    verify(error.occurred == false);
    verify(chunks != NULL);
    verify(chunks->length == 4);

    struct string* chunk;
    chunk = array_get(chunks, 0);
    verify(strneq(chunk->content, "example", chunk->length));
    chunk = array_get(chunks, 1);
    verify(strneq(chunk->content, "string", chunk->length));
    chunk = array_get(chunks, 2);
    verify(strneq(chunk->content, "with", chunk->length));
    chunk = array_get(chunks, 3);
    verify(strneq(chunk->content, "separators\n", chunk->length));


  success();
    memory_release(&allocator);
}
