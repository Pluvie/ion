#include "json_decode.h"

spec( json_decode ) {
  argument(str* source);
  argument(void* target);
  argument(struct reflection* reflection);
  argument(struct allocator* allocator);

  precondition("a valid allocator");
  #define preconditions \
    allocator = spec_allocator;

  when("the JSON is valid and all fields are reflected") {
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
      "  },"                                  "\n"
      "  \"numbers\": ["                      "\n"
      "    0,"                                "\n"
      "    1,"                                "\n"
      "    2,"                                "\n"
      "    3"                                 "\n"
      "  ],"                                  "\n"
      "  \"matrix\": ["                       "\n"
      "    1.1, 1.1, 1.1,"                    "\n"
      "    2.2, 2.2, 2.2,"                    "\n"
      "    3.3, 3.3, 3.3"                     "\n"
      "  ]"                                   "\n"
      "}"
    );
    apply(preconditions);
    reflection = &example_reflection;
    target = &example;

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

      verify(example.numbers.length == 4);
      verify(*list<int>_at(&example.numbers, 0) == 0);
      verify(*list<int>_at(&example.numbers, 1) == 1);
      verify(*list<int>_at(&example.numbers, 2) == 2);
      verify(*list<int>_at(&example.numbers, 3) == 3);

      verify(example.matrix[0][0] == 1.1);
      verify(example.matrix[0][1] == 1.1);
      verify(example.matrix[0][2] == 1.1);
      verify(example.matrix[1][0] == 2.2);
      verify(example.matrix[1][1] == 2.2);
      verify(example.matrix[1][2] == 2.2);
      verify(example.matrix[2][0] == 3.3);
      verify(example.matrix[2][1] == 3.3);
      verify(example.matrix[2][2] == 3.3);

    success();
  } end();

  when("the JSON is valid and there are unreflected fields") {
    source = &string(
      "{"                                       "\n"
      "  \"coordinates\": ["                    "\n"
      "    {"                                   "\n"
      "      \"x\": -3.78811961027628e-30,"     "\n"
      "      \"y\": 5.0777519828370644e+29,"    "\n"
      "      \"z\": 0.3911777618872192,"        "\n"
      "      \"name\": \"wrilcf 4052\","        "\n"
      "      \"opts\": {"                       "\n"
      "        \"1\": ["                        "\n"
      "          1,"                            "\n"
      "          true"                          "\n"
      "        ]"                               "\n"
      "      }"                                 "\n"
      "    },"                                  "\n"
      "    {"                                   "\n"
      "      \"x\": -3.8364965301388495e-30,"   "\n"
      "      \"y\": 4.6040112540920864e+30,"    "\n"
      "      \"z\": 0.41726476470994134,"       "\n"
      "      \"name\": \"xgjvnu 1782\","        "\n"
      "      \"opts\": {"                       "\n"
      "        \"1\": ["                        "\n"
      "          1,"                            "\n"
      "          true"                          "\n"
      "        ]"                               "\n"
      "      }"                                 "\n"
      "    },"                                  "\n"
      "    {"                                   "\n"
      "      \"x\": -8.960830174173817e-31,"    "\n"
      "      \"y\": 3.204940355350686e+30,"     "\n"
      "      \"z\": 0.36483814414317295,"       "\n"
      "      \"name\": \"xsqzng 5051\","        "\n"
      "      \"opts\": {"                       "\n"
      "        \"1\": ["                        "\n"
      "          1,"                            "\n"
      "          true"                          "\n"
      "        ]"                               "\n"
      "      }"                                 "\n"
      "    }"                                   "\n"
      "  ],"                                    "\n"
      "  \"info\": \"some info\""               "\n"
      "}"
    );
    apply(preconditions);
    target = &coordinates_data;
    reflection = &coordinates_data_reflection;

    json_decode(source, target, reflection, allocator);

    must("correctly decode the JSON to the target struct");
      verify(failure.occurred == false);
  }
}
