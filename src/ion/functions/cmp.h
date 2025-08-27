/**
 * Predefined comparison functions for ⚡️ION⚡️ base types. */

static inline int cmp<int> (
    int v1,
    int v2
);

static inline int cmp<dec> (
    dec v1,
    dec v2
);

static inline int cmp<bool> (
    bool v1,
    bool v2
);

static inline int cmp<char*> (
    char* v1,
    char* v2
);

static inline int cmp<string> (
    string v1,
    string v2
);

static inline int cmp<string, char*> (
    string v1,
    char* v2
);

static inline int cmp<char*, string> (
    char* v1,
    string v2
);
