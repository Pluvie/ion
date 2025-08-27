/**
 * Overridable macro to define comparisons for user defined types.
 *
 * For example, suppose you define the type:
 *
 * ```c
 * struct book {
 *   string isbn;
 *   string title;
 * };
 * ```
 *
 * Naturally, to compare to books, you want to just check their `isbn`, since it's
 * unique for each book, whereas the `title` may be the same for two different books,
 * thus resulting in incorrect comparisons.
 *
 * To use this logic in data structures that utilize type comparison, such as a
 * `set<struct book>`, you can define your `cmp<struct book>` function like this:
 *
 * ```c
 * int cmp<struct book> (
 *   struct book b1,
 *   struct book b2 
 * )
 * {
 *   return cmp<string>(b1.isbn, b2.isbn);
 * }
 * ```
 *
 * And then override the `cmp` macro like this:
 *
 * ```c
 * #undef cmp
 * #define cmp(v1, v2)                  \
 *   _Generic(v1,                       \
 *     struct book : cmp<struct book>,  \
 *     _cmp(v1, v2)                     \
 *   )(v1, v2)
 * ```
 *
 * If you don't override this macro, the default `cmp` macro won't compile, as your
 * type will not match the generic type expression.
 *
 * This of course should be done exactly once for a whole program, only when all used
 * types are known, and must be updated every time a new type is added. */
#define cmp(v, ...) \
  _Generic((v), _cmp(v, __VA_ARGS__))(v, __VA_ARGS__)


/**
 * Default comparison for ⚡️ION⚡️ base types. */
#define _cmp(v, ...)                \
  int : cmp<int>,                   \
  dec : cmp<dec>,                   \
  bool : cmp<bool>,                 \
  string : cmp<string>,             \
  struct io* : cmp<struct io*>
