spec( string_to_int ) {

  argument(string source);

  when("the source string contains a valid integer number") {
    source = s("17788");
    int result = string_to_int(source);

    must("not fail");
      verify(unlikely(failure.occurred) == false);

    must("convert the string to its integer equivalent");
      verify((int) 17788 == result);

    success();
  } end();

  when("the source string does not contain a valid integer number") {
    source = s("17aaa:0");
    int result = string_to_int(source);

    must("fail with a specific error");
      verify(unlikely(failure.occurred) == true);
      verify(streq(failure.message,
        "cannot convert `17aaa:0` to int: invalid characters detected"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();
}
