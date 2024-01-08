#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

/**
 * print_char - prints a character
 * @ch: character to print
 * @count: pointer to the count of printed characters
 */
void print_char(char ch, int *count)
{
	*count += write(1, &ch, 1);
}

/**
 * print_string - prints a string
 * @str: string to print
 * @count: pointer to the count of printed characters
 */
void print_string(const char *str, int *count)
{
	if (str != NULL)
		*count += write(1, str, strlen(str));
	else
		*count += write(1, "(null)", 6);
}

/**
 * print_number - prints a number (int)
 * @num: number to print
 * @count: pointer to the count of printed characters
 */
void print_number(int num, int *count)
{

	{
		int divisor = 1;
		int digit;

		/* Handle negative numbers */
		if (num < 0)
		{
			*count += write(1, "-", 1);
			num = -num;
		}

		/* Convert digits to characters and print */
		while (num / divisor > 9)
			divisor *= 10;
		while (divisor != 0)
		{
			digit = num / divisor + '0';
			*count += write(1, &digit, 1);
			num %= divisor;
			divisor /= 10;
		}
	}
}
/**
 * _printf - similar to printf function
 * Description: simulates printf function
 * @format: input to the printf function
 * Return: the number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	int count = 0;
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
					print_char(va_arg(args, int), &count);
					break;
				case 's':
					print_string(va_arg(args, const char*), &count);
					break;
				case 'd':
				case 'i':
					print_number(va_arg(args, int), &count);
					break;
				case '%':
					count += write(1, "%", 1);
					break;
				default:
					count += write(1, "%", 1) + write(1, format, 1);
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
