spec( reflection ) {

  when("reflecting an array type") {
    when("the array type is reflected directly") {
      int cube[3][3][3];
      struct reflection rfx = {
        type(ARRAY, int[3][3][3]), of({ type(INT) })
      };

      must("correctly define the reflection");
        verify(rfx.type == ARRAY);
        verify(strnull(rfx.name));
        verify(streq(rfx.type_name, "i64[3][3][3]"));
        verify(rfx.size == sizeof(cube));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.element != NULL);

        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == INT);
        verify(strnull(element_rfx->name));
        verify(strnull(element_rfx->type_name));
        verify(element_rfx->size == sizeof(int));
        verify(element_rfx->offset == 0);
        verify(element_rfx->index == 0);

      success();
    } end();

    when("the array type is reflected by reference") {
      struct chess_square {
        bool is_occupied;
        string piece;
      };
      struct chess_square chess_board[8][8];

      struct reflection rfx = {
        /* Using `typeof` to reference the array type. */
        type(ARRAY, typeof(chess_board)), of({
          type(STRUCT, struct chess_square), fields({
            { field(is_occupied, BOOL, struct chess_square) },
            { field(piece, STRING, struct chess_square) },
          })
        })
      };

      must("correctly define the reflection");
        verify(rfx.type == ARRAY);
        verify(strnull(rfx.name));
        verify(streq(rfx.type_name, "typeof(chess_board)"));
        verify(rfx.size == sizeof(chess_board));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.element != NULL);

        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == STRUCT);
        verify(strnull(element_rfx->name));
        verify(streq(element_rfx->type_name, "struct chess_square"));
        verify(element_rfx->size == sizeof(struct chess_square));
        verify(element_rfx->offset == 0);
        verify(element_rfx->index == 0);
        verify(element_rfx->fields != NULL);
        verify(element_rfx->fields->length == 2);

        struct reflection* field_rfx;
        field_rfx = list_at(element_rfx->fields, 0);
        verify(field_rfx->type == BOOL);
        verify(streq(field_rfx->name, "is_occupied"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(bool));
        verify(field_rfx->offset == offsetof(struct chess_square, is_occupied));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 1);
        verify(field_rfx->type == STRING);
        verify(streq(field_rfx->name, "piece"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(string));
        verify(field_rfx->offset == offsetof(struct chess_square, piece));
        verify(field_rfx->index == 0);


      success();
    } end();

    when("the array type is reflected by inference") {
      struct example {
        int value_int;
        struct {
          int value_int;
          dec value_dec;
        } why[3];
      };

      struct reflection rfx = {
        type(STRUCT, struct example), fields({
          { field(value_int, INT, struct example) },
          { field(why, ARRAY, struct example), of({
              /* Since the array is a tagless struct, we must use the type inference
               * macro `o` to get the array type. */
              type(STRUCT, typeof(*o(struct example)->why)), fields({
                { field(value_int, INT, typeof(*o(struct example)->why)) },
                { field(value_dec, DEC, typeof(*o(struct example)->why)) },
              })
            })
          },
        }),
      };


      must("correctly define the reflection");
        verify(rfx.type == STRUCT);
        verify(strnull(rfx.name));
        verify(streq(rfx.type_name, "struct example"));
        verify(rfx.size == sizeof(struct example));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.fields != NULL);
        verify(rfx.fields->length == 2);

        struct reflection* field_rfx;
        field_rfx = list_at(rfx.fields, 0);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "value_int"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct example, value_int));
        verify(field_rfx->index == 0);

        field_rfx = list_at(rfx.fields, 1);
        verify(field_rfx->type == ARRAY);
        verify(streq(field_rfx->name, "why"));
        verify(streq(field_rfx->type_name, "struct example"));
        verify(field_rfx->size == sizeof(o(struct example)->why));
        verify(field_rfx->offset == offsetof(struct example, why));
        verify(field_rfx->index == 0);
        verify(field_rfx->element != NULL);

        struct reflection* element_rfx;
        element_rfx = field_rfx->element;
        verify(element_rfx->type == STRUCT);
        verify(strnull(element_rfx->name));
        verify(streq(element_rfx->type_name, "typeof(*((struct example*) 0)->why)"));
        verify(element_rfx->size == sizeof(*o(struct example)->why));
        verify(element_rfx->offset == 0);
        verify(element_rfx->index == 0);
        verify(element_rfx->fields != NULL);
        verify(element_rfx->fields->length == 2);

        field_rfx = list_at(element_rfx->fields, 0);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "value_int"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_int));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 1);
        verify(field_rfx->type == DEC);
        verify(streq(field_rfx->name, "value_dec"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(dec));
        verify(field_rfx->offset == offsetof(typeof(*o(struct example)->why), value_dec));
        verify(field_rfx->index == 0);

      success();
    } end();
  } end();

  when("reflecting a struct type") {
    when("the struct type is reflected directly") {
      struct example {
        int value_int;
        dec value_dec;
      };

      struct reflection rfx = {
        type(STRUCT, struct example), fields({
          { field(value_int, INT, struct example) },
          { field(value_dec, DEC, struct example) },
        }),
      };

      must("correctly define the reflection");
        verify(rfx.type == STRUCT);
        verify(strnull(rfx.name));
        verify(streq(rfx.type_name, "struct example"));
        verify(rfx.size == sizeof(struct example));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.fields != NULL);
        verify(rfx.fields->length == 2);

        struct reflection* field_rfx;
        field_rfx = list_at(rfx.fields, 0);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "value_int"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct example, value_int));
        verify(field_rfx->index == 0);

        field_rfx = list_at(rfx.fields, 1);
        verify(field_rfx->type == DEC);
        verify(streq(field_rfx->name, "value_dec"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(dec));
        verify(field_rfx->offset == offsetof(struct example, value_dec));
        verify(field_rfx->index == 0);

      success();
    } end();

    when("the struct type is reflected by defining") {
      struct example {
        int value_int;
        dec value_dec;
        struct {
          char* text;
          int number;
          struct {
            char* text;
            int number;
          } inside_2;
        } inside_1;
      };

      /* We can define the struct type to a constant to avoid repeated typing. */
      #define t struct example
      struct reflection rfx = {
        type(STRUCT, t), fields({
          { field(value_int, INT, t) },
          { field(value_dec, DEC, t) },
          { field(inside_1, STRUCT, t), fields({
              { field(text, POINTER, t, inside_1), of({ type(CHAR) }) },
              { field(number, INT, t, inside_1) },
              { field(inside_2, STRUCT, t, inside_1), fields({
                  { field(text, POINTER, t, inside_1.inside_2), of({ type(CHAR) }) },
                  { field(number, INT, t, inside_1.inside_2) },
                })
              },
            })
          },
        }),
      };
      #undef t

      must("correctly define the reflection");
        verify(rfx.type == STRUCT);
        verify(strnull(rfx.name));
        verify(streq(rfx.type_name, "struct example"));
        verify(rfx.size == sizeof(struct example));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.fields != NULL);
        verify(rfx.fields->length == 3);

        struct reflection* field_rfx;
        field_rfx = list_at(rfx.fields, 0);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "value_int"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct example, value_int));
        verify(field_rfx->index == 0);

        field_rfx = list_at(rfx.fields, 1);
        verify(field_rfx->type == DEC);
        verify(streq(field_rfx->name, "value_dec"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(dec));
        verify(field_rfx->offset == offsetof(struct example, value_dec));
        verify(field_rfx->index == 0);

        struct example example;
        struct reflection* inside_1_rfx = list_at(rfx.fields, 2);
        verify(inside_1_rfx->type == STRUCT);
        verify(streq(inside_1_rfx->name, "inside_1"));
        verify(strnull(inside_1_rfx->type_name));
        verify(inside_1_rfx->size == sizeof(example.inside_1));
        verify(inside_1_rfx->offset == offsetof(struct example, inside_1));
        verify(inside_1_rfx->index == 0);
        verify(inside_1_rfx->fields != NULL);
        verify(inside_1_rfx->fields->length == 3);

        field_rfx = list_at(inside_1_rfx->fields, 0);
        verify(field_rfx->type == POINTER);
        verify(streq(field_rfx->name, "text"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(void*));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.text) - offsetof(struct example, inside_1));
        verify(field_rfx->index == 0);

        field_rfx = list_at(inside_1_rfx->fields, 1);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "number"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.number) - offsetof(struct example, inside_1));
        verify(field_rfx->index == 0);

        struct reflection* inside_2_rfx = list_at(inside_1_rfx->fields, 2);
        verify(inside_2_rfx->type == STRUCT);
        verify(streq(inside_2_rfx->name, "inside_2"));
        verify(strnull(inside_2_rfx->type_name));
        verify(inside_2_rfx->size == sizeof(example.inside_1.inside_2));
        verify(inside_2_rfx->offset ==
          offsetof(struct example, inside_1.inside_2) - offsetof(struct example, inside_1));
        verify(inside_2_rfx->index == 0);
        verify(inside_2_rfx->fields != NULL);
        verify(inside_2_rfx->fields->length == 2);

        field_rfx = list_at(inside_2_rfx->fields, 0);
        verify(field_rfx->type == POINTER);
        verify(streq(field_rfx->name, "text"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(void*));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.inside_2.text) -
          offsetof(struct example, inside_1.inside_2));
        verify(field_rfx->index == 0);

        field_rfx = list_at(inside_2_rfx->fields, 1);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "number"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.inside_2.number) -
          offsetof(struct example, inside_1.inside_2));
        verify(field_rfx->index == 0);

      success();
    } end();

    when("the struct type is reflected by offsetting") {
      struct example {
        int value_int;
        dec value_dec;
        struct {
          char* text;
          int number;
          struct {
            char* text;
            int number;
          } inside_2;
        } inside_1;
      };

      struct reflection rfx = {
        type(STRUCT, struct example), fields({
          { field(value_int, INT, struct example) },
          { field(value_dec, DEC, struct example) },
          { field(inside_1, STRUCT, struct example), fields({
              { field(text, POINTER, struct example, inside_1),
                  of({ type(CHAR) })
              },
              { field(number, INT, struct example, inside_1) },
              { field(inside_2, STRUCT, struct example, inside_1), fields({
                  /* The struct `inside_2` is tagless so we must use an offset from
                   * `inside_1` to get its type. */
                  { field(text, POINTER, struct example, inside_1.inside_2),
                      of({ type(CHAR) })
                  },
                  { field(number, INT, struct example, inside_1.inside_2) },
                })
              },
            })
          },
        }),
      };

      must("correctly define the reflection");
        verify(rfx.type == STRUCT);
        verify(strnull(rfx.name));
        verify(streq(rfx.type_name, "struct example"));
        verify(rfx.size == sizeof(struct example));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.fields != NULL);
        verify(rfx.fields->length == 3);

        struct reflection* field_rfx;
        field_rfx = list_at(rfx.fields, 0);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "value_int"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct example, value_int));
        verify(field_rfx->index == 0);

        field_rfx = list_at(rfx.fields, 1);
        verify(field_rfx->type == DEC);
        verify(streq(field_rfx->name, "value_dec"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(dec));
        verify(field_rfx->offset == offsetof(struct example, value_dec));
        verify(field_rfx->index == 0);

        struct example example;
        struct reflection* inside_1_rfx = list_at(rfx.fields, 2);
        verify(inside_1_rfx->type == STRUCT);
        verify(streq(inside_1_rfx->name, "inside_1"));
        verify(strnull(inside_1_rfx->type_name));
        verify(inside_1_rfx->size == sizeof(example.inside_1));
        verify(inside_1_rfx->offset == offsetof(struct example, inside_1));
        verify(inside_1_rfx->index == 0);
        verify(inside_1_rfx->fields != NULL);
        verify(inside_1_rfx->fields->length == 3);

        field_rfx = list_at(inside_1_rfx->fields, 0);
        verify(field_rfx->type == POINTER);
        verify(streq(field_rfx->name, "text"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(void*));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.text) - offsetof(struct example, inside_1));
        verify(field_rfx->index == 0);

        field_rfx = list_at(inside_1_rfx->fields, 1);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "number"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.number) - offsetof(struct example, inside_1));
        verify(field_rfx->index == 0);

        struct reflection* inside_2_rfx = list_at(inside_1_rfx->fields, 2);
        verify(inside_2_rfx->type == STRUCT);
        verify(streq(inside_2_rfx->name, "inside_2"));
        verify(strnull(inside_2_rfx->type_name));
        verify(inside_2_rfx->size == sizeof(example.inside_1.inside_2));
        verify(inside_2_rfx->offset ==
          offsetof(struct example, inside_1.inside_2) - offsetof(struct example, inside_1));
        verify(inside_2_rfx->index == 0);
        verify(inside_2_rfx->fields != NULL);
        verify(inside_2_rfx->fields->length == 2);

        field_rfx = list_at(inside_2_rfx->fields, 0);
        verify(field_rfx->type == POINTER);
        verify(streq(field_rfx->name, "text"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(void*));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.inside_2.text) -
          offsetof(struct example, inside_1.inside_2));
        verify(field_rfx->index == 0);

        field_rfx = list_at(inside_2_rfx->fields, 1);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "number"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset ==
          offsetof(struct example, inside_1.inside_2.number) -
          offsetof(struct example, inside_1.inside_2));
        verify(field_rfx->index == 0);

      success();
    } end();
  } end();

  when("reflecting a list type") {
    when("the list reflection has no limits") {
      list<struct squadmate> squad;

      struct reflection rfx = {
        type(LIST), of({
          type(STRUCT, struct squadmate), fields({
            { field(name, STRING, struct squadmate) },
            { field(class, ENUM, struct squadmate) },
            { field(health, INT, struct squadmate) },
            { field(shields, INT, struct squadmate) },
          }),
        }),
      };

      must("correctly define the reflection");
        verify(rfx.type == LIST);
        verify(strnull(rfx.name));
        verify(strnull(rfx.type_name));
        verify(rfx.size == sizeof(squad));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.element != NULL);

        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == STRUCT);
        verify(strnull(element_rfx->name));
        verify(streq(element_rfx->type_name, "struct squadmate"));
        verify(element_rfx->size == sizeof(struct squadmate));
        verify(element_rfx->offset == 0);
        verify(element_rfx->index == 0);
        verify(element_rfx->fields != NULL);
        verify(element_rfx->fields->length == 4);

        struct reflection* field_rfx;
        field_rfx = list_at(element_rfx->fields, 0);
        verify(field_rfx->type == STRING);
        verify(streq(field_rfx->name, "name"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(struct string));
        verify(field_rfx->offset == offsetof(struct squadmate, name));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 1);
        verify(field_rfx->type == ENUM);
        verify(streq(field_rfx->name, "class"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(enum classes));
        verify(field_rfx->offset == offsetof(struct squadmate, class));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 2);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "health"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, health));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 3);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "shields"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, shields));
        verify(field_rfx->index == 0);

      success();
    } end();

    when("the list reflection has limits") {
      list<struct squadmate> squad;

      struct reflection rfx = {
        type(LIST), limited_to(4, 8), of({
          type(STRUCT, struct squadmate), fields({
            { field(name, STRING, struct squadmate) },
            { field(class, ENUM, struct squadmate) },
            { field(health, INT, struct squadmate) },
            { field(shields, INT, struct squadmate) },
          }),
        }),
      };

      must("correctly define the reflection");
        verify(rfx.type == LIST);
        verify(strnull(rfx.name));
        verify(strnull(rfx.type_name));
        verify(rfx.size == sizeof(squad));
        verify(rfx.size_limits.min == 4);
        verify(rfx.size_limits.max == 8);
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.element != NULL);

        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == STRUCT);
        verify(strnull(element_rfx->name));
        verify(streq(element_rfx->type_name, "struct squadmate"));
        verify(element_rfx->size == sizeof(struct squadmate));
        verify(element_rfx->offset == 0);
        verify(element_rfx->index == 0);
        verify(element_rfx->fields != NULL);
        verify(element_rfx->fields->length == 4);

        struct reflection* field_rfx;
        field_rfx = list_at(element_rfx->fields, 0);
        verify(field_rfx->type == STRING);
        verify(streq(field_rfx->name, "name"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(struct string));
        verify(field_rfx->offset == offsetof(struct squadmate, name));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 1);
        verify(field_rfx->type == ENUM);
        verify(streq(field_rfx->name, "class"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(enum classes));
        verify(field_rfx->offset == offsetof(struct squadmate, class));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 2);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "health"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, health));
        verify(field_rfx->index == 0);

        field_rfx = list_at(element_rfx->fields, 3);
        verify(field_rfx->type == INT);
        verify(streq(field_rfx->name, "shields"));
        verify(strnull(field_rfx->type_name));
        verify(field_rfx->size == sizeof(int));
        verify(field_rfx->offset == offsetof(struct squadmate, shields));
        verify(field_rfx->index == 0);

      success();
    } end();

    when("the list type is nested") {
      list<list<int>> table;

      struct reflection rfx = {
        type(LIST), of({
          type(LIST), of({
            type(INT)
          }),
        }),
      };

      must("correctly define the reflection");
        verify(rfx.type == LIST);
        verify(rfx.size == sizeof(table));
        verify(strnull(rfx.name));
        verify(strnull(rfx.type_name));
        verify(rfx.index == 0);
        verify(rfx.offset == 0);
        verify(rfx.element != NULL);

        struct reflection* element_rfx = rfx.element;
        verify(element_rfx->type == LIST);
        verify(strnull(element_rfx->name));
        verify(strnull(element_rfx->type_name));
        verify(element_rfx->size == sizeof(list<int>));
        verify(element_rfx->offset == 0);
        verify(element_rfx->index == 0);
        verify(element_rfx->element != NULL);

        element_rfx = element_rfx->element;
        verify(element_rfx->type == INT);
        verify(strnull(element_rfx->name));
        verify(strnull(element_rfx->type_name));
        verify(element_rfx->size == sizeof(int));
        verify(element_rfx->offset == 0);
        verify(element_rfx->index == 0);

      success();
    } end();
  } end();
}
