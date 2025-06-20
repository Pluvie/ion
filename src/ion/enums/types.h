enum types {
  INT,        /* 64bit signed integer */
  DEC,        /* 64bit double precision decimal */
  CHAR,       /* 8bit ascii char */
  BOOL,       /* 32bit boolean */
  ENUM,       /* 32bit enumeration */
  STRING,     /* 128bit string pointer with incorporated length */
  STRUCT,     /* Nbit struct */
  ARRAY,      /* fixed length array */
  POINTER,    /* 64bit pointer */
  SELF,       /* 64bit pointer to same type */
  LIST,       /* list data structure */
  MAP,        /* map data structure */
  SET,        /* set data structure */

  TYPES_COUNT,
};
