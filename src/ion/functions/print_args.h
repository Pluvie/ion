int print_args (
    void* output,
    int length,
    va_list args
);

int print_bool (void* output, int length, bool* value);
int print_char (void* output, int length, char* value);
int print_char_unsigned (void* output, int length, unsigned char* value);
int print_int0 (void* output, int length, int0* value);
int print_int (void* output, int length, int* value);
int print_int_unsigned (void* output, int length, unsigned int* value);
int print_dec (void* output, int length, dec* value);
int print_str (void* output, int length, str* value);
int print_char_pointer (void* output, int length, char** value);
int print_void_pointer (void* output, int length, void** value);
