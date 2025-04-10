enum type_sizes;
/**
 * Explain what enum types does and why it's useful for reflection. */
enum type_sizes {
  U8__SIZE        = 1,  /* unsigned integer : 1 byte. */
  U16__SIZE       = 2,  /* unsigned integer : 2 bytes. */
  U32__SIZE       = 4,  /* unsigned integer : 4 bytes. */
  U64__SIZE       = 8,  /* unsigned integer : 8 bytes. */
  I8__SIZE        = 1,  /* signed integer   : 1 byte. */
  I16__SIZE       = 2,  /* signed integer   : 2 bytes. */
  I32__SIZE       = 4,  /* signed integer   : 4 bytes. */
  I64__SIZE       = 8,  /* signed integer   : 8 bytes. */
  D32__SIZE       = 4,  /* signed decimal   : 4 bytes. */
  D64__SIZE       = 8,  /* signed decimal   : 8 bytes. */
  D128__SIZE      = 16, /* signed decimal   : 16 bytes. */
  BYTE__SIZE      = 1,  /* hex byte         : 1 byte. */
  CHAR__SIZE      = 1,  /* ascii char       : 1 byte. */
  BOOL__SIZE      = 1,  /* boolean          : 1 byte. */
  STRING__SIZE    = 16, /* string           : 16 bytes. */
  STRUCT__SIZE    = 0,  /* struct           : n bytes. */
  POINTER__SIZE   = 8,  /* pointer          : 8 bytes. */
  SEQUENCE__SIZE  = 0,  /* sequence         : n bytes. */
  ARRAY__SIZE     = 64, /* array            : 64 bytes. */
  VECTOR__SIZE    = 32, /* vectors          : 32 bytes. */
};
