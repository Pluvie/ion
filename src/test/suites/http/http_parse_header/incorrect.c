test( http_parse_header, incorrect ) {

  given("an incorrect HTTP header");
    char* header_content = "Content-Type application/json\r\n";
    struct io input = io_open_memory(header_content, strlen(header_content));


  calling("http_parse_header()");
    struct memory allocator = memory_init(0);
    struct http_header header = http_parse_header(&input, &allocator);


  must("fail to parse the header with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message,
      "HTTP header name must be a token: no spaces or delimiters allowed, "
        "at position 13:\n"
      "Content-Type application/json\r\n"
      "            ^"));
    verify(header.name.content == NULL);
    verify(header.value.content == NULL);


  success();
    memory_release(&allocator);
}
