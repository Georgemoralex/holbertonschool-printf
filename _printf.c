#include <unistd.h>
#include <stdarg.h>
#include <string.h>

/**
 * _printf - simulates printf function
 * @format: input to the printf function
 * Return: the number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    if (!format)
        return -1;

    va_list args;
    va_start(args, format);

    int count = 0;
    char ch, *str;

    while (format && *format)
    {
        if (*format == '%' && *(++format))
        {
            switch (*format)
            {
                case 'c':
                    count += write(1, &ch, 1), ch = va_arg(args, int);
                    break;
                case 's':
                    str = va_arg(args, char *);
                    count += write(1, str ? str : "(null)", str ? strlen(str) : 6);
                    break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    count += write(1, "%", 1) + write(1, format - 1, 1);
            }
        }
        else
        {
            count += write(1, format, 1);
        }

        format++;
    }
    va_end(args);
    return count;
}
