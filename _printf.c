/**
 * _printf - A simplified implementation of the printf function
 * Description: This function emulates the basic functionality of printf,
 *              allowing the printing of characters ('c'), strings ('s'),
 *              and the '%' character. It takes a format string and a variable
 *              number of arguments and writes the formatted output to the
 *              standard output (file descriptor 1). It does not handle
 *              advanced features such as flags, field width, precision, or
 *              length modifiers.
 * @format: The format string containing format specifiers.
 * Return: The number of characters successfully printed (excluding the null byte),
 *         or -1 if the format string is NULL.
 */
int _printf(const char *format, ...)
{
    int count = 0;
    char ch;
    const char *str;
    va_list args;

    // Check if the format string is NULL
    if (format == NULL)
        return (-1);

    // Initialize the va_list for variable arguments
    va_start(args, format);

    // Iterate through the format string
    while (format && *format)
    {
        // Check if the current character is '%'
        if (*format == '%')
        {
            format++;

            // Check if '%' is followed by the null terminator
            if (*format == '\0')
                return (-1);

            // Switch based on the character following '%'
            switch (*format)
            {
                case 'c':
                    // Retrieve and print a character argument
                    ch = va_arg(args, int);
                    count += write(1, &ch, 1);
                    break;

                case 's':
                    // Retrieve and print a string argument
                    str = va_arg(args, const char*);
                    if (str != NULL)
                        count += write(1, str, strlen(str));
                    else
                        count += write(1, "(null)", 6);
                    break;

                case '%':
                    // Print the '%' character
                    count += write(1, "%", 1);
                    break;

                default:
                    // Print '%' and the current character
                    count += write(1, "%", 1);
                    count += write(1, format, 1);
                    break;
            }
        }
        else
        {
            // Print the current character
            count += write(1, format, 1);
        }

        // Move to the next character in the format string
        format++;
    }

    // Clean up the va_list variable
    va_end(args);

    // Return the total count of characters printed
    return (count);
}
