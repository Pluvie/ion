test( json_parse_number, integer ) {

  given("a json number");
    char* json;


  when("the number is an integer");
    json = "1245";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct sci_notation number = json_parse_number(&input);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(number.negative == false);
    verify(strneq(number.integer.content, "1245", 4));


  success();
}
