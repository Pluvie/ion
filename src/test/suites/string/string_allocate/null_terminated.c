test( string_allocate, null_terminated ) {

  given("an allocator");
    struct memory allocator = memory_init(0);


  calling("string_allocate()");
    u64 length = 3;
    struct string* string = string_allocate(length, &allocator);


  must("allocate the string with null terminated content");
    verify(error.occurred == false);
    verify(string->length == length);
    verify(string->content != NULL);
    verify(string->content[string->length] == '\0');


  success();
    memory_release(&allocator);
}
