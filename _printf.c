#include <unistd.h>
#include <stdarg.h>
#include <string.h>

/**
 * _printf - similar to printf function
 * @format: input to the printf function
 * Return: the number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    int count = 0;
    va_list args;

    if (!format)
        return -1;

    va_start(args, format);

    while (format && *format)
    {
        if (*format == '%' && *(++format))
        {
            switch (*format)
            {
                case 'c':
                {
                    char ch = (char)va_arg(args, int);
                    count += write(1, &ch, 1);
                }
                break;
                case 's':
                    {
                        const char *str = va_arg(args, const char *);
                        int len = va_arg(args, int);
                        count += write(1, str ? str : "(null)", str ? len : 6);
                    }
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