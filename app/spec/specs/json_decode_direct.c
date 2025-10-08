#include "json_decode_direct.h"

spec( json_decode_direct ) {
  argument(struct io_direct* io);
  argument(struct reflection* reflection);
  argument(void* target);

  precondition("a valid reflection");
  precondition("a valid target for that reflection");
  #define preconditions \
    reflection = nullptr; \
    target = nullptr;

  when("the io contains a valid JSON") {
    string json = string(
      "{"                               "\n"
      "  \"int\":     12345,"           "\n"
      "  \"dec\":     777.7E-30,"       "\n"
      "  \"string\":  \"value\","       "\n"
      "  \"bool\":    true,"            "\n"
      "  \"array\": ["                  "\n"
      "    12345,"                      "\n"
      "    77.7E+30,"                   "\n"
      "    \"string\","                 "\n"
      "    null,"                       "\n"
      "    {"                           "\n"
      "      \"bool\":  false"          "\n"
      "    }"                           "\n"
      "  ]"                             "\n"
      "}"
    );
    io = &(struct io_direct) { &json, json.chars };
    apply(preconditions);

    json_decode_direct(io, reflection, target);
    printl();
    if (failure.occurred)
      printl(PRINT_COLOR_RED, failure.message, PRINT_COLOR_NONE);

    must("do something");
      verify(reflection == nullptr);
      verify(target == nullptr);
      verify(true);

    success();
  } end();
}
