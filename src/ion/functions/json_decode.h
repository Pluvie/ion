void json_decode (
    struct io* io,
    void* target
);



static inline void json_decode_direct (
    struct io_direct* io,
    void* target
);



static inline void json_decode_buffered (
    struct io_buffered* io,
    void* target
);
