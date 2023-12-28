#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int _printf(const char *format, ...) {
    if (format == NULL) {
        write(1, "(null format string)", 20);
        return -1;
    }

    va_list args;
    va_start(args, format);

    int count = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c':
                    {
                        char ch = va_arg(args, int);
                        count += write(1, &ch, 1);
                    }
                    break;
                case 's':
                    {
                        const char* str = va_arg(args, const char*);
                        if (str == NULL) {
                            count += write(1, "(null)", 6);
                        } else {
                            count += write(1, str, strlen(str));
                        }
                    }
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    break;
            }
        } else {
            count += write(1, format, 1);
        }
        format++;
    }
    va_end(args);
    return count;
}
