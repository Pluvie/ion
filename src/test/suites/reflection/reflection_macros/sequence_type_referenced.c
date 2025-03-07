test( reflection_macros, sequence_type_referenced ) {

  given("a sequence");
    struct chess_square {
      bool is_occupied;
      struct string occupying_piece;
    };
    struct chess_square chess_board[8][8];


  calling("the reflection macros with the `typeof` reference");
    struct reflection rfx = {
      type(SEQUENCE, typeof(chess_board)), of({
        type(STRUCT, struct chess_square), fields({
          { field(is_occupied, BOOL, struct chess_square) },
          { field(occupying_piece, STRING, struct chess_square) },
        })
      })
    };


  must("correctly define the reflection");
    verify(rfx.type == SEQUENCE);
    verify(rfx.size == sizeof(chess_board));
    verify(rfx.index == 0);
    verify(rfx.offset == 0);
    verify(rfx.name == NULL);
    verify(rfx.element != NULL);

    struct reflection* element_rfx = rfx.element;
    verify(element_rfx->type == STRUCT);
    verify(element_rfx->size == sizeof(struct chess_square));
    verify(element_rfx->offset == 0);
    verify(element_rfx->index == 0);
    verify(element_rfx->fields != NULL);
    verify(element_rfx->fields->length == 2);

    struct reflection* field_rfx;
    field_rfx = vector_get(element_rfx->fields, 0);
    verify(field_rfx->type == BOOL);
    verify(field_rfx->size == sizeof(bool));
    verify(field_rfx->offset == offsetof(struct chess_square, is_occupied));
    verify(streq(field_rfx->name->content, "is_occupied"));
    verify(field_rfx->index == 0);

    field_rfx = vector_get(element_rfx->fields, 1);
    verify(field_rfx->type == STRING);
    verify(field_rfx->size == sizeof(struct string));
    verify(field_rfx->offset == offsetof(struct chess_square, occupying_piece));
    verify(streq(field_rfx->name->content, "occupying_piece"));
    verify(field_rfx->index == 0);


  success();
}
