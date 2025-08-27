/**
 * Predefined comparison functions for ⚡️ION⚡️ base types. */

int cmp<int> (
    int v1,
    int v2
);

int cmp<dec> (
    dec v1,
    dec v2
);

int cmp<bool> (
    bool v1,
    bool v2
);

int cmp<char*> (
    char* v1,
    char* v2
);

int cmp<string> (
    string v1,
    string v2
);

int cmp<string, char*> (
    string v1,
    char* v2
);

int cmp<char*, string> (
    char* v1,
    string v2
);
