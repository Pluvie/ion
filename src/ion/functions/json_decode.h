void json_decode (
    struct io* io,
    void* target
);



static inline void json_decode_direct (
    struct io_direct* io,
    struct reflection* rfx,
    void* target
);



static inline void json_decode_buffered (
    struct io_buffered* io,
    struct reflection* rfx,
    void* target
);
