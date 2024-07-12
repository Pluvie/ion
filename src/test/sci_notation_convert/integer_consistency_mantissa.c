test( sci_notation_convert, integer_consistency_mantissa ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is integer");
    enum types type = I64;


  when("the number has a mantissa");
    number.negative = true;
    number.integer.content = "100";
    number.integer.length = 3;
    number.mantissa.content = "001";
    number.mantissa.length = 3;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert to (I64): number has a mantissa"));


  success();
}
