/**
 * Defines an tensor type declination. */
#define tensor(...)             _tensor(__VA_ARGS__)
#define _tensor(t)              tensor__ ## t

/* Defines all tensor declined symbols. */
#define tensor_allocate(...)    _tensor_allocate(__VA_ARGS__)
#define _tensor_allocate(t)     tensor_allocate__ ## t
#define tensor_init(...)        _tensor_init(__VA_ARGS__)
#define _tensor_init(t)         tensor_init__ ## t
#define tensor_at(...)          _tensor_at(__VA_ARGS__)
#define _tensor_at(t)           tensor_at__ ## t
#define tensor_iterator(...)    _tensor_iterator(__VA_ARGS__)
#define _tensor_iterator(t)     tensor_iterator ## t
