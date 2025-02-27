focus_test( csv_decode_row, correct_columns ) {

  given("a csv file");
    char* csv_file =
      "name;age;height;weight"    "\n"
      "Eugene;17;1.77;77"         "\n"
      "Eugene;17;1.77;77"         "\n"
      "Eugene;17;1.77;77"         "\n"
      "Eugene;17;1.77;77"         "\n";
    struct csv_properties csv = {
      .separator = ';',
      .wrapper = 0,
      .columns_count = 4,
      .encoding = UTF_8,
    };
    struct memory allocator = memory_init(0);


  when("it has an associated reflection");
    struct athlete {
      char* name;
      u32 age;
      u32 height;
      u32 weight;
    } athlete;

    struct reflect athlete_reflection = {
      type(STRUCT, sizeof(struct athlete)), fields({
        { field(struct athlete, name), type(POINTER), of({ type(CHAR) }) },
        { field(struct athlete, age), type(U32) },
        { field(struct athlete, height), type(D64) },
        { field(struct athlete, weight), type(U32) },
      })
    };


  when("the csv headers are mapped correctly");
    struct map headers = map_init(sizeof(u64), sizeof(struct csv_header), 0, &allocator);
    map_set(&headers, &(u64) { 0 }, & (struct csv_header) {
      .index = 0,
      .name = &s("name"),
      .target = &(struct object) {
        .reflection = vector_get(athlete_reflection.child, 0),
        .allocator = &allocator,
      }
    });
    map_set(&headers, &(u64) { 1 }, & (struct csv_header) {
      .index = 1,
      .name = &s("age"),
      .target = &(struct object) {
        .reflection = vector_get(athlete_reflection.child, 1),
        .allocator = &allocator,
      }
    });
    map_set(&headers, &(u64) { 2 }, & (struct csv_header) {
      .index = 2,
      .name = &s("height"),
      .target = &(struct object) {
        .reflection = vector_get(athlete_reflection.child, 2),
        .allocator = &allocator,
      }
    });
    map_set(&headers, &(u64) { 3 }, & (struct csv_header) {
      .index = 3,
      .name = &s("weight"),
      .target = &(struct object) {
        .reflection = vector_get(athlete_reflection.child, 3),
        .allocator = &allocator,
      }
    });


  calling("csv_decode_row()");
    struct object athlete_object = object(athlete, &athlete_reflection);
    athlete_object.allocator = &allocator;
    struct io source = io_memory(csv_file, strlen(csv_file));
    source.cursor = 23;
    csv_decode_row(&source, &athlete_object, &headers, csv);


  must("decode the row correctly");
    verify(error.occurred == false);
    verify(athlete.age == 17);


  success();
    memory_release(&allocator);
}
