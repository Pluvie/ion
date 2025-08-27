spec( string_index ) {

  argument(string source);
  argument(string tester);

  when("the source string is empty and the tester string is empty") {
    source = (string) { 0 };
    tester = (string) { 0 };

    int idx = string_index(source, tester);

    must("return -1");
      verify(idx == -1);

    success();
  } end();

  when("the source string is empty and the tester string is not empty") {
    source = (string) { 0 };
    tester = s("abc");

    int idx = string_index(source, tester);

    must("return -1");
      verify(idx == -1);

    success();
  } end();

  when("the source string is not empty and the tester string is empty") {
    source = s("abc");
    tester = (string) { 0 };

    int idx = string_index(source, tester);

    must("return -1");
      verify(idx == -1);

    success();
  } end();

  when("the source string is not empty and the tester string is not empty") {
    when("the source string begins with the tester string") {
      source = s("abcdef");
      tester = s("ab");

      int idx = string_index(source, tester);

      must("return the source index on which the tester is included");
        verify(idx == 0);

      success();
    } end();

    when("the source string contains the tester string") {
      source = s("abcdef");
      tester = s("cd");

      int idx = string_index(source, tester);

      must("return the source index on which the tester is included");
        verify(idx == 2);

      success();
    } end();

    when("the source string ends with the tester string") {
      source = s("abcdef");
      tester = s("ef");

      int idx = string_index(source, tester);

      must("return the source index on which the tester is included");
        verify(idx == 4);

      success();
    } end();

    when("the source string does not contain the tester string") {
      source = s("abcdef");
      tester = s("xyz");

      int idx = string_index(source, tester);

      must("return -1");
        verify(idx == -1);

      success();
    } end();
  } end();
}
