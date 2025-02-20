test( json_parse_string, buffer_optimization_socket_huge ) {

  given("a huge json string");
    char json[] =
      "\"Very long string that surpasses 256 characters, which is the default peek "
      "window of the json_parse_string function. The peek window is introduced to "
      "optimize io from file or sockets, where each io_read function call executes "
      "a system call -- fread for files, recv for sockets. Since JSON string parsing "
      "is done char by char, it would not be efficient to execute a system call for "
      "every character! Expecially for long strings like this one. So, the peek window "
      "is introduced, which peeks from the io a growing amount of characters, and saves "
      "it in memory -- using the struct buffer. Then, the actual character parsing is "
      "done by reading from memory, which is much more efficient.\"";


  when("the string is read from a socket");
    recv_simulated_data = &io_reader(json, sizeof(json));
    struct io input = {
      .channel = IO_CHANNEL_SOCK,
      .mode = IO_MODE_READ,
    };


  calling("json_parse_string()");
    u64 string_length = json_parse_string(&input);


  must("parse the string correctly and optimize the number of reads");
    verify(error.occurred == false);
    verify(string_length == strlen(json));
    verify(input.reads_count == 3);


  success();
}
