#include <unistd.h>
#include <stdarg.h>
#include <string.h>

/**
 * _printf - similar to printf function
 * Description: simulates printf function
 * @format: input to the printf function
 * Return: the number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	int count = 0;
	char ch;
	const char *str;
	va_list args;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (format && *format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (-1);

			switch (*format)
			{
				case 'c':
				{
					ch = va_arg(args, int);
					count += write(1, &ch, 1);
				}
				break;
				case 's':
				{
					str = va_arg(args, const char*);
					if (str != NULL)
					{
						count += write(1, str, strlen(str));
					}
					else
						count += write(1, "(null)", 6);
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
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
