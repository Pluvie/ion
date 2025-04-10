/**
 * The `string` type is a little improvement on the classical `char*`, oftentimes
 * improperly used as string.
 *
 * The main differences between the two are:
 *   1. The `string` type has a `length` field which, at the cost of storing extra
 *      8 bytes, can provide the string length in constant time.
 *   2. The `string` type is not NUL-terminated, since its length is known a priori.
 *
 * Interoperability with stdlib functions is granted by the `content` field, which is
 * a `char*` type. Beware that the `string` type is not NUL-terminated though! Only
 * use stdlib functions that explicitly require a length argument -- like `snprintf`,
 * `strncpy`, etc.
 *
 * `string` literals can be created using the macro `s`, example:
 *
 * ```c
 * string name = s("Kovalski");
 * ```
 *
 * This macro shall calculate the length at compile time. */
typedef struct string {
  char* content;
  u64 length;
} string;
check_sizeof(string, 16);
