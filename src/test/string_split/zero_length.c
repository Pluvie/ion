test( string_split, zero_length ) {

  given("a string");
    struct string string = s("");


  calling("string_split()");
    struct memory allocator = memory_init(0);
    struct array* chunks = string_split(string, &allocator, ';', 0);


  must("split the string into an empty array of chunks");
    verify(error.occurred == false);
    verify(chunks != NULL);
    verify(chunks->length == 0);


  success();
    memory_release(&allocator);
}
