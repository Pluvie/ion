spec( string_to_dec ) {

  argument(string source);

  when("the source string contains a valid decimal number") {
    source = s("177.88");
    dec result = string_to_dec(source);

    must("not fail");
      verify(unlikely(failure.occurred) == false);

    must("convert the string to its decimal equivalent");
      verify((dec) 177.88 == result);

    success();
  } end();

  when("the source string does not contain a valid decimal number") {
    source = s("17aaa:0");
    dec result = string_to_dec(source);

    must("fail with a specific error");
      verify(unlikely(failure.occurred) == true);
      verify(streq(failure.message,
        "cannot convert `17aaa:0` to dec: invalid characters detected"));

    must("return 0");
      verify((dec) 0 == result);

    success();
  } end();
}
