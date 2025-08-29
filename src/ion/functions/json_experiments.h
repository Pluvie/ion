bool json<T>_parse_null_direct (
    struct io* io,
    T* source
);

bool json<T>_parse_bool_direct (
    struct io* io,
    T* source
);

bool json<T>_parse_number_direct (
    struct io* io,
    T* source
);

void json<T>_decode_direct (
    struct io* io,
    T* source
);
