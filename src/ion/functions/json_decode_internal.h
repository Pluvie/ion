/*
  Declares all internal functions used by the JSON decoding suite.
*/

static inline void json_decode_array (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_array_as_array (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_array_as_list (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_array_as_set (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
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

static inline void json_decode_number_as_dec (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_number_as_int (
    str* source,
    void* target,
    struct reflection* reflection
);

static inline void json_decode_object (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_object_as_struct (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_decode_object_as_map (
    str* source,
    void* target,
    struct reflection* reflection,
    struct allocator* allocator
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
    struct reflection* reflection,
    struct allocator* allocator
);

static inline void json_discard_array (
    str* source
);

static inline void json_discard_object (
    str* source
);

static inline void json_discard_number (
    str* source
);

static inline void json_discard_spaces (
    str* source
);
