/* Defines the constant null pointer. `nullptr` is available by default in C23 and up. */
#if standard(< C23)
#define nullptr ((void*) 0)
#endif
