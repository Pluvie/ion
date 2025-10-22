/*
 The `failure` type is used to trace a program failure.

 Example program flow:

 ```c
 void failing_function (
     void
 )
 {
   if (read(...) == -1) {
     fail("failed to read from xyz");
     return;
   }
   other_stuff();
 }

 int0 main (
     int0 argc,
     char** argv
 )
 {
   failing_function();
   if (unlikely(failure.occurred)) {
     failure_print();
     return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
 }

 ```
*/
struct failure {
  bool occurred;
  char message[511];
};
