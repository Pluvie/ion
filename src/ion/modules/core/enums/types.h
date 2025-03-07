enum types;
/**
 * Explain what enum types does and why it's useful for reflection. */
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
  STRING,     /* string           : 16 bytes. */
  STRUCT,     /* struct           : n bytes. */
  POINTER,    /* pointer          : 8 bytes. */
  SEQUENCE,   /* sequence         : n bytes. */
  ARRAY,      /* array            : 64 bytes. */
  VECTOR,     /* vectors          : 32 bytes. */
};
