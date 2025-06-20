/**
 * Overridable macro to define hash calculation for user defined types.
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
 * Naturally, to calculate the hash of a book, you want to just use its `isbn`,
 * since it's unique for each book, whereas the `title` may be the same for two
 * different books and thus resulting in hash collisions.
 *
 * To use this logic in data structures that utilize hash calculations, such
 * as a `set<struct book>`, you can define your `hash<struct book>` function like this:
 *
 * ```c
 * int hash<struct book> (
 *   struct book book
 * )
 * {
 *   return hash<string>(book.isbn);
 * }
 * ```
 *
 * And then override the `hash` macro like this:
 *
 * ```c
 * #undef hash
 * #define hash(v)                      \
 *   _Generic(v,                        \
 *     struct book : hash<struct book>, \
 *     _hash(v)                         \
 *   )(v)
 * ```
 *
 * If you don't override this macro, the default `hash` macro won't compile, as your
 * type will not match the generic type expression.
 *
 * This of course should be done exactly once for a whole program, only when all used
 * types are known, and must be updated every time a new type is added. */
#define hash(v) \
  _Generic((v), _hash(v))(v)


/**
 * Default hash for ⚡️ION⚡️ base types. */
#define _hash(v)          \
  int : hash<int>,        \
  dec : hash<dec>,        \
  bool : hash<bool>,      \
  char : hash<char>,      \
  char* : hash<char*>,    \
  string : hash<string>
