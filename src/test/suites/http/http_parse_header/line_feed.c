test( http_parse_header, line_feed ) {

  given("an HTTP header terminated only by line feed");
    char* header_content = "Content-Type: text/html; charset=utf-8\n";
    struct io input = io_open_memory(header_content, strlen(header_content));


  calling("http_parse_header()");
    struct memory allocator = memory_init(0);
    struct http_header header = http_parse_header(&input, &allocator);


  must("successfully parse the header for compatibility purposes");
    verify(error.occurred == false);
    verify(strncaseeq(header.name.content,
      "content-type", lengthof("content-type")));
    hexdump(header.value.content, header.value.length);
    verify(strncaseeq(header.value.content,
      "text/html; charset=UTF-8", lengthof("text/html; charset=UTF-8")));


  success();
    memory_release(&allocator);
}
