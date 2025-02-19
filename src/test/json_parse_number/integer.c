test( json_parse_number, integer ) {

  given("a json number");
    char* json;


  when("the number is an integer");
    json = "1245";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    i32 number;
    json_parse_number(&input, I32, &number);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(number == 1245);


  success();
}
