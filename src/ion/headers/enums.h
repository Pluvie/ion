enum types;
/**
 * Explain what enum types does and why it's useful for reflection and serialization. */
enum types {
  U8,         /* unsigned integer : 1 byte. */
  U16,        /* unsigned integer : 2 bytes. */
  U32,        /* unsigned integer : 4 bytes. */
  U64,        /* unsigned integer : 8 bytes. */
  I8,         /* signed integer   : 1 byte. */
  I16,        /* signed integer   : 2 bytes. */
  I32,        /* signed integer   : 4 bytes. */
  I64,        /* signed integer   : 8 bytes. */
  D32,        /* signed decimal   : 4 bytes. */
  D64,        /* signed decimal   : 8 bytes. */
  D128,       /* signed decimal   : 16 bytes. */
  BYTE,       /* hex byte         : 1 byte. */
  CHAR,       /* ascii char       : 1 byte. */
  BOOL,       /* boolean          : 1 byte. */
  ARRAY,      /* array            : n byte. */
  STRUCT,     /* struct           : n byte. */
  POINTER,    /* pointer          : n bytes. */
  SEQUENCE,   /* sequence         : n bytes. */
};

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




enum io_flags;
/**
 * Flags used to control which operations are allowed on an io object. */
enum io_flags {
  IO_NONE   = 0,
  IO_READ   = 1,
  IO_WRITE  = 2,
};

