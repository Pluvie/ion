spec( *function_name* ) {

  argument(*argument_type* *argument_name*);
  argument(*argument_type* *argument_name*);

  precondition("some description of one precondition");
  precondition("some description of another precondition");
    #define preconditions \
      *first_precondition* = 0; \
      *second_precondition* = 1;

  when("a description of a specific context") {
    when("a description of a specific nested context") {
      must("a description of what is expected");
      must("another description of what is expected") {
        apply(preconditions);
        *some statements to define the specific context*;
        *some statements to define the specific context*;
        *result_type* *result_name* = *function_name*(*argument*, *argument*, ...);
        verify(*a boolean statement to be verified*);
        verify(*a boolean statement to be verified*);
      }
    }
  }

  when("...") {
    must("...");
    must("...");
    must("...") {
      apply(precondition);
      verify(...);
    }
  }

  #undef preconditions
}
