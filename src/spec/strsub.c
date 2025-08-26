spec( strsub ) {

  argument(string source);
  argument(int begin);
  argument(int end);

  when("the source string is empty") {
    source = (string) { 0 };
    begin = 7;
    end = 9;

    string sub = strsub(source, begin, end);

    must("return an empty string");
      verify(strnull(sub));

    success();
  } end();

  when("the source string is not empty") {
    when("the end value is negative") {
      source = s("abcdef");
      begin = 2;
      end = -3;

      string sub = strsub(source, begin, end);

      must("return the substring counting from the end of the string");
        verify(streq(sub, "cd"));

      success();
    } end();

    when("the end value is positive") {
      source = s("abcdef");
      begin = 2;
      end = 4;

      string sub = strsub(source, begin, end);

      must("return the substring from begin to end inclusive");
        verify(streq(sub, "cde"));

      success();
    } end();

    when("the begin value is greater than the end value") {
      source = s("abcdef");
      begin = 6;
      end = 4;

      string sub = strsub(source, begin, end);

      must("return an empty string");
        verify(strnull(sub));

      success();
    } end();
  } end();
}
