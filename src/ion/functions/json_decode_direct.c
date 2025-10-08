static inline void json_decode_array_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_false_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_null_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_number_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_number_dec_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_number_int_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_object_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_string_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_true_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

static inline void json_decode_value_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
);

#define io_advance(io, amount)          io->cursor += amount
#define io_contains(io, value, length)  memory_equal(io->cursor, value, length)
#define io_cursor(io)                   (io->cursor)
#define io_exhausted(io)                (*(io->cursor) == 0)

#define json_parse_array    json_decode_array_direct(io, reflection, target)
#define json_parse_false    json_decode_false_direct(io, reflection, target)
#define json_parse_null     json_decode_null_direct(io, reflection, target)
#define json_parse_number   json_decode_number_direct(io, reflection, target)
#define json_parse_object   json_decode_object_direct(io, reflection, target)
#define json_parse_string   json_decode_string_direct(io, reflection, target)
#define json_parse_true     json_decode_true_direct(io, reflection, target)
#define json_parse_value    json_decode_value_direct(io, reflection, target)

void json_decode_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  printl();
  json_decode_value_direct(io, reflection, target);
  if (unlikely(failure.occurred)) {
    char error[1024] = { 0 };
    unsigned int position = io->data->chars - io->cursor;
    memory_copy(error, io->cursor, io->data->length);
    error[position] = '%';
    fail("json error: ", failure.message, "\n", error);
  }
}

static inline void json_decode_array_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  #define json_parse_array_init     /* logic to initialize the array */
  #define json_parse_array_member   json_decode_value_direct(io, reflection, target)

  #include "../procedures/json_parse_array.c"

  #undef json_parse_array_init
  #undef json_parse_array_member
}

static inline void json_decode_false_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  printl(">> boolean false");
}

static inline void json_decode_null_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  printl(">> null");
}

static inline void json_decode_number_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  return json_decode_number_int_direct(io, reflection, target);
}

static inline void json_decode_number_dec_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
}

static inline void json_decode_number_int_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  int result = 0;

  #define cursor io->cursor
  #define PARSE_NUMBER__INTEGER
  #include "../procedures/parse_number.c"
  #undef  PARSE_NUMBER__INTEGER
  #undef  cursor

procedure_success:
  printl(">> number: ", f(result));
  //return result;

procedure_failure:
  //return 0;
}

static inline void json_decode_object_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  #define json_parse_object_init \
    printl(">> object begin");

  #define json_parse_object_member_name \
    printl(">> object member name: ", f(object_member_name));

  #define json_parse_object_member_value \
    json_decode_value_direct(io, reflection, target)

  #include "../procedures/json_parse_object.c"

  #undef json_parse_object_init
  #undef json_parse_object_member_name
  #undef json_parse_object_member_value
}

static inline void json_decode_string_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  string result = { 0 };
  #include "../procedures/json_parse_string.c"
  *(string*) target = result;
}

static inline void json_decode_true_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  printl(">> boolean true");
}

static inline void json_decode_value_direct (
    struct io_direct* io,
    struct reflection* reflection,
    void* target
)
{
  #include "../procedures/json_parse_value.c"
}

#undef json_parse_array
#undef json_parse_false
#undef json_parse_null
#undef json_parse_number
#undef json_parse_object
#undef json_parse_string
#undef json_parse_true
#undef json_parse_value

#undef io_advance
#undef io_contains
#undef io_cursor
#undef io_exhausted
