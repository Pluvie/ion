spec( strstart ) {

  argument(string source);
  argument(string tester);

  when("the source string is empty and the tester string is empty") {
    source = (string) { 0 };
    tester = (string) { 0 };

    bool result = strstart(source, tester);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the source string is empty and the tester string is not empty") {
    source = (string) { 0 };
    tester = s("abc");

    bool result = strstart(source, tester);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the source string is not empty and the tester string is empty") {
    source = s("abc");
    tester = (string) { 0 };

    bool result = strstart(source, tester);

    must("return false");
      verify(result == false);

    success();
  } end();

  when("the source string is not empty and the tester string is not empty") {
    when("the source string begins with the tester string") {
      source = s("abcdef");
      tester = s("ab");

      bool result = strstart(source, tester);

      must("return true");
        verify(result == true);

      success();
    } end();

    when("the source string contains the tester string") {
      source = s("abcdef");
      tester = s("cd");

      bool result = strstart(source, tester);

      must("return false");
        verify(result == false);

      success();
    } end();

    when("the source string ends with the tester string") {
      source = s("abcdef");
      tester = s("ef");

      bool result = strstart(source, tester);

      must("return false");
        verify(result == false);

      success();
    } end();

    when("the source string does not contain the tester string") {
      source = s("abcdef");
      tester = s("xyz");

      bool result = strstart(source, tester);

      must("return false");
        verify(result == false);

      success();
    } end();
  } end();
}
