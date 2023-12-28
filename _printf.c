#include <unistd.h>
#include <stdarg.h>
#include <string.h>

int _printf(const char *format, ...) {
    int count = 0;
    va_list args;

    if (format == NULL) {
        return -1;
    }

    va_start(args, format);

    while (format && *format) {
        if (*format == '%') {
            format++;
            if (*format == '\0') {
                break;
            }
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
                        if (str != NULL) {
                            count += write(1, str, strlen(str));
                        } else {
                            count += write(1, "(null)", 6);
                        }
                    }
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    count += write(1, "%", 1);
                    count += write(1, format, 1);
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