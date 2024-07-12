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
  /* ARRAY, STRUCT, POINTER and SEQUENCE do not have a size known a priori. */
  0,    /* ARRAY */
  0,    /* STRUCT */
  0,    /* POINTER */
  0,    /* SEQUENCE */
};

const char* type_names[] = {
  "U8",
  "U16",
  "U32",
  "U64",
  "I8",
  "I16",
  "I32",
  "I64",
  "D32",
  "D64",
  "D128",
  "BYTE",
  "CHAR",
  "BOOL",
  "ARY",
  "STRU",
  "PTR",
  "SEQ",
};
