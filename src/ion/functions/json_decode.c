static inline void json_decode_array (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_false (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_null (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_number (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_number_dec (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_number_int (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_object (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_string (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_true (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_value (
    str* source,
    void* target,
    struct reflection* reflection
);

#define json_advance(source, amount)          source->chars += amount
#define json_contains(source, value, length)  memory_equal(source->chars, value, length)
#define json_cursor(source)                   (source->chars)
#define json_exhausted(source)                (*(source->chars) == 0)

#define json_parse_array    json_decode_array(source, target, reflection)
#define json_parse_false    json_decode_false(source, target, reflection)
#define json_parse_null     json_decode_null(source, target, reflection)
#define json_parse_number   json_decode_number(source, target, reflection)
#define json_parse_object   json_decode_object(source, target, reflection)
#define json_parse_string   json_decode_string(source, target, reflection)
#define json_parse_true     json_decode_true(source, target, reflection)
#define json_parse_value    json_decode_value(source, target, reflection)

void json_decode (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  printl();
  char* source_begin = source->chars;
  json_decode_value(source, target, reflection);

  if (unlikely(failure.occurred)) {
    char error[1024] = { 0 };
    unsigned int position = source->chars - source_begin;
    printl(">>>>>>> position: ", f(position));
    memory_copy(error, source_begin, source->length);
    error[position] = '%';
    fail("json error: ", failure.message, "\n", error);
  }
}

static inline void json_decode_array (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  #define json_parse_array_init \
    printl(">> array begin");

  #define json_parse_array_member \
    json_decode_value(source, target, reflection)

  #include "../procedures/json_parse_array.c"

  #undef json_parse_array_init
  #undef json_parse_array_member
}

static inline void json_decode_false (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  printl(">> boolean false");
}

static inline void json_decode_null (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  printl(">> null");
}

static inline void json_decode_number (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  //return json_decode_number_int(source, target, reflection);
  return json_decode_number_dec(source, target, reflection);
}

static inline void json_decode_number_dec (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  dec result = 0;

  #define cursor source->chars
  #define PARSE_NUMBER__DECIMAL
  #include "../procedures/parse_number.c"
  #undef  PARSE_NUMBER__DECIMAL
  #undef  cursor

procedure_success:
  printl(">> number: ", f(result));
  //return result;

procedure_failure:
  //return 0;
}

static inline void json_decode_number_int (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  int result = 0;

  #define cursor source->chars
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

static inline void json_decode_object (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  #define json_parse_object_init \
    printl(">> object begin");

  #define json_parse_object_member_name \
    printl(">> object member name: ", f(object_member_name));

  #define json_parse_object_member_value \
    json_decode_value(source, target, reflection)

  #include "../procedures/json_parse_object.c"

  #undef json_parse_object_init
  #undef json_parse_object_member_name
  #undef json_parse_object_member_value
}

static inline void json_decode_string (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  str result = { 0 };
  #include "../procedures/json_parse_string.c"
  //*(str*) target = result;
}

static inline void json_decode_true (
    str* source,
    void* target,
    struct reflection* reflection
)
{
  printl(">> boolean true");
}

static inline void json_decode_value (
    str* source,
    void* target,
    struct reflection* reflection
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

#undef json_advance
#undef json_contains
#undef json_cursor
#undef json_exhausted
