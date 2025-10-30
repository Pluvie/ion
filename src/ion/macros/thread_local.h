/* Portable declaration of thread local storage. */
#if standard(>= C11)
#define thread_local  _Thread_local

#elif compiler(MSVC)
#define thread_local  __declspec(thread)

#elif compiler(GCC) || compiler(CLANG)
#define thread_local  __thread

#else
#define thread_local

#endif
