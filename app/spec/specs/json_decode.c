#include "json_decode.h"

spec( json_decode ) {
  argument(str* source);
  argument(void* target);
  argument(struct reflection* reflection);
  argument(struct allocator* allocator);

  precondition("a valid reflection");
  precondition("a valid target for that reflection");
  precondition("a valid allocator");
  #define preconditions \
    reflection = &example_reflection; \
    target = &example; \
    allocator = spec_allocator;

  when("the io contains a valid JSON") {
    source = &string(
      "{"                                     "\n"
      "  \"integer\": 12345,"                 "\n"
      "  \"decimal\": 777.7E-30,"             "\n"
      "  \"string\": \"value\","              "\n"
      "  \"boolean\": true,"                  "\n"
      "  \"strings\": ["                      "\n"
      "    \"string 1\","                     "\n"
      "    \"string 2\","                     "\n"
      "    null,"                             "\n"
      "    \"string 4\""                      "\n"
      "  ],"                                  "\n"
      "  \"squad\": {"                        "\n"
      "    \"garrus\": {"                     "\n"
      "      \"name\": \"Garrus Vakarian\","  "\n"
      "      \"class\": 2,"                   "\n"
      "      \"health\": 200,"                "\n"
      "      \"shields\": 400"                "\n"
      "    },"                                "\n"
      "    \"wrex\": {"                       "\n"
      "      \"name\": \"Urdnot Wrex\","      "\n"
      "      \"class\": 1,"                   "\n"
      "      \"health\": 800,"                "\n"
      "      \"shields\": 800"                "\n"
      "    }"                                 "\n"
      "  }"                                   "\n"
      "}"
    );
    apply(preconditions);

    json_decode(source, target, reflection, allocator);

    printl();
    if (failure.occurred)
      printl(PRINT_COLOR_RED, failure.message, PRINT_COLOR_NONE);

    must("do something");
      verify(true);

    success();
  } end();
}
