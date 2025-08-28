spec( io_test ) {

  string str = s("aaaabbbbccccdddd");
  struct io io_string = io(&str, NULL, NULL);

  struct file file = file_open(s("tmp/json_decode_old.c"));
  struct io io_file = io(&file, NULL, NULL);

  char* result_string = io_read(&io_string, &str, 10);

  char data[64] = { 0 };
  char* result_file = io_read(&io_file, &file, 10, data);

  verify(result_string == str.pointer);
  verify(result_file == data);
  verify(io_string.cursor == 10);
  verify(io_file.cursor == 10);

  success();
    file_close(&file);
}
