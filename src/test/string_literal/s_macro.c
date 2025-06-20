test( string_literal, s_macro ) {

  given("a string");
  calling("the s macro to initialize the string");
    string str = s("Hello String!");


  must("initialize content and length");
    verify(str.length == lengthof("Hello String!"));
    verify(strncmp(str.content, "Hello String!", str.length) == 0);


  success();
}
