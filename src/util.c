#include "util.h"

#include "peripherals/uart.h"

/* ASCII character to integer */
int hex_char_to_int(char ch)
{
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }

    if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    }

    if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    }

    return -1;
}

/* ASCII to what (?) - TODO(roemvaar) Implement this conversion */
char a2i(char ch, char **src, int base, int *nump)
{
    (void)ch;
    (void)src;
    (void)base;
    (void)nump;

    return 'a';
}

/* Unsigned int to ascii string */
void ui2a(unsigned int num, unsigned int base, char *bf)
{
    int n = 0;
    int dgt;
    unsigned int d = 1;

    while ((num / d) >= base) {
        d *= base;
    }

    while (d != 0) {
        dgt = num / d;
        num %= d;
        d /= base;

        if (n || dgt > 0 || d == 0) {
            *bf++ = dgt + (dgt < 10 ? '0' : 'a' - 10);
            ++n;
        }
    }

    *bf = 0;
}

/* Signed int to ascii string */
void i2a(int num, char *bf)
{
    if (num < 0) {
        num = -num;
        *bf++ = '-';
    }

    ui2a(num, 10, bf);
}

void print_oso_logo(void)
{
    const char *bear_art =
        " __         __\r\n"
        "/  \\.-\"\"\"-./  \\\r\n"
        "\\    -   -    /\r\n"
        " |   o   o   |\r\n"
        " \\  .-'''-.  /\r\n"
        "  '-\\__Y__/-'\r\n"
        "     `---`\r\n"
        "\r\n"
        "\r\n";

    uart_printf(CONSOLE, "%s", bear_art);
}

// /* Just used for debugging certain */
// void print_debug()
// {
//     uart_printf(1, "DEBUG PRINT\r\n");
//     return;
// }
