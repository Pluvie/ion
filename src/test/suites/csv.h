#include "../../ion/modules/csv.c"

#include "csv/csv_decode/detect_headers.c"
#include "csv/csv_decode/no_headers.c"
#include "csv/csv_decode_headers/matching_fields.c"
#include "csv/csv_decode_headers/unmatching_fields.c"
#include "csv/csv_decode_row/field_types.c"
#include "csv/csv_is_reflection_compatible/compatible.c"
#include "csv/csv_is_reflection_compatible/incompatible_struct_fields.c"
#include "csv/csv_is_reflection_compatible/not_array.c"
#include "csv/csv_is_reflection_compatible/not_array_of_struct.c"
#include "csv/csv_parse_row/comma_separated.c"
#include "csv/csv_parse_row/comma_separated_wrapped.c"
#include "csv/csv_parse_row/comma_separated_overcount.c"
#include "csv/csv_parse_row/malformed_wrapper.c"
#include "csv/csv_parse_row/multiple_rows.c"
#include "csv/csv_parse_row/multiple_rows_mixed.c"
#include "csv/csv_parse_row/newline_unwrapped.c"
#include "csv/csv_parse_row/newline_unwrapped_overcount.c"
#include "csv/csv_parse_row/semicolon_separated.c"
#include "csv/csv_parse_row/semicolon_separated_wrapped.c"
#include "csv/csv_string_split/array_of_chunks.c"
#include "csv/csv_string_split/wrapped.c"
#include "csv/csv_string_split/wrapped_incomplete.c"
#include "csv/csv_string_split/wrapped_unterminated.c"
#include "csv/csv_string_split/zero_length.c"
