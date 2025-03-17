test( reflection_inspect, print_object ) {

  given("a reflection");
    struct example {
      u64 index;
      u64 value;
      struct string* name;
      d128** dbl_ptr;
      struct { 
        i32 value;
      } inner;
      byte seq[4];
      byte seq2[4][4];
      struct array* values;
      struct array* users;
      void* empty;
    };

    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(index, U64, struct example) },
        { field(value, U64, struct example) },
        { field(name, POINTER, struct example), of({ type(STRING) }) },
        { field(dbl_ptr, POINTER, struct example), of({ type(POINTER), of({ type(D128) }) }) },
        { field(inner, STRUCT, struct example), fields({
            { field(value, I32, struct example, inner) }
          })
        },
        { field(seq, SEQUENCE, struct example), of({ type(BYTE) }) },
        { field(seq2, SEQUENCE, struct example), of({ type(BYTE) }) },
        { field(values, POINTER, struct example), of({ type(ARRAY), of({ type(I64) }) }) },
        { field(users, POINTER, struct example), of({ type(ARRAY), of({
          type(STRUCT, struct { u32 age; struct string name; }), fields({
            { field(age, U32, struct { u32 age; struct string name; }) },
            { field(name, STRING, struct { u32 age; struct string name; }) },
          }) }) })
        },
        { field(empty, POINTER, struct example), of({ type(BYTE) }) },
      })
    };


  when("an object is associated to this reflection");
    d128 v = 7.7;
    d128* vv = &v;
    struct example object = {
      .index = 9,
      .value = 33,
      .dbl_ptr = &vv,
      .name = &s("object"),
      .inner.value = 11,
      .seq = { 0xaa, 0xab, 0xac, 0xad },
      .seq2 = { { 0xba, 0xbb, 0xbc, 0xbd }, { 0xca, 0xcb, 0xcc, 0xcd }, },
      .values = &array_of(i64, { -3, 0, 7 }),
      .users = &array_of(struct { u32 age; struct string name; }, {
        { .age = 17, .name = s("Mary") },
        { .age = 24, .name = s("Joseph") },
      }),
      .empty = NULL,
    };


  calling("reflection_inspect()");
    inspect(&object, &rfx);


  must("print the object data");


  success();
}
