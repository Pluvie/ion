spec( json_decode_self ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      struct rfx_blueprint blueprint = { 0 }; \
      obj = &(blueprint.v_self); \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      struct reflection* blueprint_rfx = &(struct reflection) { \
        type(STRUCT, struct rfx_blueprint), fields({ \
          { field(v_int, INT, struct rfx_blueprint) }, \
          { field(v_self, SELF, struct rfx_blueprint) }, \
        }) \
      }; \
      rfx = reflection_field_find(blueprint_rfx, s("v_self")); \
      allocator = spec_allocator;

  when("the json object has the matching field") {
    apply(preconditions);
    *io = io(s("   \n { \"v_int\": \"123\", "\
      "\"v_self\": { \"v_int\": 456, \"v_self\": null } } "));
    io->cursor = 33;
    json_decode_self(obj, io, rfx, allocator);

    must("not fail");
      verify(error.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 65);
    must("set the correct value to the corresponding field");
      verify(blueprint.v_self->v_int == 456);
      verify(blueprint.v_self->v_self == NULL);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
