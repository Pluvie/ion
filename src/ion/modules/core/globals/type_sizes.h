/**
 * Contains the size in bytes of every ION type. */
u32 type_sizes[] = {
  1,    /* U8 */
  2,    /* U16 */
  4,    /* U32 */
  8,    /* U64 */
  1,    /* I8 */
  2,    /* I16 */
  4,    /* I32 */
  8,    /* I64 */
  4,    /* D32 */
  8,    /* D64 */
  16,   /* D128 */
  1,    /* BYTE */
  1,    /* CHAR */
  1,    /* BOOL */
  16,   /* STRING */
  0,    /* STRUCT does not have a size known a priori. */
  8,    /* POINTER */
  0,    /* SEQUENCE does not have a size known a priori. */
  64,   /* ARRAY */
  32,   /* VECTOR */
};
