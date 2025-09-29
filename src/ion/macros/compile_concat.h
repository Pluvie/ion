/*
  Concatenates two preprocessor tokens.
*/
#define compile_concat(prefix, suffix) \
  compile_concat_indirect(prefix, suffix)




/*
  Layer of macro indirection to make the #compile_concat macro work.
*/
#define compile_concat_indirect(prefix, suffix) \
  prefix ## suffix
