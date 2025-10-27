void fatal (
    const cstr format,
    ...
)
#if compiler(GCC) || compiler(CLANG)
__attribute__ ((format (printf, 1, 2)))
#endif
;
