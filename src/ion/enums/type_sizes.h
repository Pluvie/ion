enum type_sizes {
  INT__SIZE       =  8,   /* 64bit signed integer */
  DEC__SIZE       =  8,   /* 64bit double precision decimal */
  CHAR__SIZE      =  1,   /* 8bit ascii char */
  BOOL__SIZE      =  4,   /* 32bit boolean */
  ENUM__SIZE      =  4,   /* 32bit enumeration */
  STRING__SIZE    = 16,   /* 128bit string pointer with incorporated length */
  STRUCT__SIZE    =  0,   /* struct */
  ARRAY__SIZE     =  0,   /* fixed length array */
  POINTER__SIZE   =  8,   /* 64bit pointer */
  SELF__SIZE      =  8,   /* 64bit pointer to same type */
  LIST__SIZE      = 32,   /* list data structure */
  SET__SIZE       = 48,   /* set data structure */
  MAP__SIZE       = 64,   /* map data structure */
};
