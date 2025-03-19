#include "../../ion/modules/json.c"

#include "json/json_decode/array.c"
#include "json/json_decode/array_empty.c"
#include "json/json_decode/array_maxlength.c"
#include "json/json_decode/array_minlength.c"
#include "json/json_decode/array_nested.c"
#include "json/json_decode/null_value.c"
#include "json/json_decode/primitive.c"
#include "json/json_decode/primitive_not_supported.c"
#include "json/json_decode/sequence.c"
#include "json/json_decode/sequence_overlength.c"
#include "json/json_decode/struct.c"
#include "json/json_decode/struct_empty.c"
#include "json/json_decode/vector.c"
#include "json/json_decode/vector_maxlength.c"
#include "json/json_decode/vector_minlength.c"
#include "json/json_encode/primitive.c"
#include "json/json_encode/struct.c"
#include "json/json_parse_number/error_eof.c"
#include "json/json_parse_number/error_exponent.c"
#include "json/json_parse_number/error_exponent_eof.c"
#include "json/json_parse_number/error_fractional.c"
#include "json/json_parse_number/error_fractional_eof.c"
#include "json/json_parse_number/error_hex.c"
#include "json/json_parse_number/error_number.c"
#include "json/json_parse_number/error_oct.c"
#include "json/json_parse_number/exponent.c"
#include "json/json_parse_number/exponent_negative.c"
#include "json/json_parse_number/integer.c"
#include "json/json_parse_number/integer_negative.c"
#include "json/json_parse_number/fractional.c"
#include "json/json_parse_number/fractional_negative.c"
#include "json/json_parse_string/correct.c"
#include "json/json_parse_string/escaped_double_quote.c"
#include "json/json_parse_string/escaped_other.c"
#include "json/json_parse_string/incorrect.c"
#include "json/json_parse_string/unterminated.c"
