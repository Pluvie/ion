spec( string_to_int ) {

  argument(string* source);

  precondition("a valid source string");
  precondition("the source string must have at least one padding character at the end");
    #define preconditions \
      source = memory_alloc(spec_allocator, sizeof(string));

  when("the source string contains a valid number") {
    apply(preconditions);
    *source = s("17788");
    int result = string_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17788 == result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part") {
    apply(preconditions);
    *source = s("17788.44");
    int result = string_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17788 == result);

    success();
  } end();

  when("the source string contains a valid number with a decimal part and exponent") {
    apply(preconditions);
    *source = s("17788.44e-3");
    int result = string_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17 == result);

    success();
  } end();

  when("the source string contains a valid number with an exponent") {
    apply(preconditions);
    *source = s("17788e+2");
    int result = string_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 1778800 == result);

    success();
  } end();

  when("the source string contains a valid number followed by other characters") {
    apply(preconditions);
    *source = s("17aaa:0");
    int result = string_to_int(source);

    must("not fail");
      verify(failure.occurred == false);

    must("return its integer equivalent");
      verify((int) 17 == result);

    success();
  } end();

  when("the source string contains an overflowing number") {
    apply(preconditions);
    *source = s("9223372036854775936");
    int result = string_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("number overflow"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();

  when("the source string contains a double overflowing number") {
    apply(preconditions);
    *source = s("9223372036854775939223372036854775936");
    int result = string_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("number overflow"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();

  when("the source string contains a valid number and an overflowing exponent") {
    apply(preconditions);
    *source = s("777e+100");
    int result = string_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("exponent overflow"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();

  when("the source string does not contain a valid number") {
    apply(preconditions);
    *source = s("aaa:0");
    int result = string_to_int(source);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("expected a number"));

    must("return 0");
      verify((int) 0 == result);

    success();
  } end();
}
