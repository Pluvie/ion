/**
 * Functions used only by the `streq` macro. */

static inline bool streq<string, string> (
    string s1,
    string s2
);

static inline bool streq<string, slice> (
    string s1,
    slice s2
);

static inline bool streq<slice, string> (
    slice s1,
    string s2
);

static inline bool streq<slice, slice> (
    slice s1,
    slice s2
);

static inline bool streq<string, char*> (
    string s1,
    char* s2
);

static inline bool streq<slice, char*> (
    slice s1,
    char* s2
);

static inline bool streq<char*, string> (
    char* s1,
    string s2
);

static inline bool streq<char*, slice> (
    char* s1,
    slice s2
);

static inline bool streq<char*, char*> (
    char* s1,
    char* s2
);
