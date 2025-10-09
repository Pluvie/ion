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

    must("correctly decode the JSON to the target struct");
      verify(failure.occurred == false);
      verify(example.integer == 12345);
      verify(example.decimal == 777.7E-30);
      verify(str_equal(example.string, string("value")));
      verify(example.boolean == true);

      verify(example.strings.length == 4);
      verify(set<str>_has(&example.strings, string("string 1")));
      verify(set<str>_has(&example.strings, string("string 2")));
      verify(set<str>_has(&example.strings, (str) { 0 }));
      verify(set<str>_has(&example.strings, string("string 4")));
      verify(example.squad.length == 2);

      struct squadmate* garrus =
        map<str, struct squadmate>_get(&example.squad, string("garrus"));
      verify(garrus != nullptr);
      verify(str_equal(garrus->name, string("Garrus Vakarian")));
      verify(garrus->class == INFILTRATOR);
      verify(garrus->health == 200);
      verify(garrus->shields == 400);

      struct squadmate* wrex =
        map<str, struct squadmate>_get(&example.squad, string("wrex"));
      verify(wrex != nullptr);
      verify(str_equal(wrex->name, string("Urdnot Wrex")));
      verify(wrex->class == VANGUARD);
      verify(wrex->health == 800);
      verify(wrex->shields == 800);

    success();
  } end();
}
