test( failure, fail_macro ) {

  given("a failure");
  calling("the fail macro");
    verify(error.occurred == false);
    fail("example error %i %.*s", 7, sp(s("xyz")));


  must("initialize the error with the given parameters");
    verify(error.occurred == true);
    verify(error_is("example error 7 xyz"));


  success();
}
