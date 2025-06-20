test( reflection_macros, array_type_referenced ) {

  given("a array");
    struct chess_square {
      bool is_occupied;
      string piece;
    };
    struct chess_square chess_board[8][8];


  calling("the reflection macros with the `typeof` reference");
    struct reflection rfx = {
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
}
