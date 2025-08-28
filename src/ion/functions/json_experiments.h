bool json_parse_string_direct (
    struct io* io,
    T* source
);

void json_parse_spaces_direct (
    struct io* io,
    T* source
);

bool json_parse_null_direct (
    struct io* io,
    T* source
);

bool json_parse_bool_direct (
    struct io* io,
    T* source
);

bool json_parse_number_direct (
    struct io* io,
    T* source
);

void json_decode_direct (
    struct io* io,
    T* source
);

#undef T
