#include <stdio.h>
#include <ctype.h>
static const unsigned char base85[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

#if 0
static int base85_encode(char *out, size_t max, const unsigned long *data, size_t count)
{
    size_t i;
    unsigned long n;
    while (count) {
        if (max < 1)
            return 0; /* failure */
        n = *data++;
        count--;
#ifndef USE_ASCII85
        /* rfc1924 :) */
        for (i = 0; max > 0 && i < BASE85_DIGITS; i++) {
            *out++ = base85[n % 85];
            max--;
            n /= 85;
        }
#else
        /* Ascii85 (adobe) */
        if (n == 0) {
            *out++ = 'z'; /* this is a special zero character */
            max--;
        } else {
            if (max < 5)
                return 0; /* no room */
            for (i = BASE85_DIGITS; i--;) {
                out[i] = base85[n % 85];
                n /= 85;
            }
            max -= 5;
            out += 5;
        }
#endif
    }
    *out = 0;
    return 1; /* success */
}

#endif

int main(int argc, char **argv)
{
    unsigned char ch = 1;
    while (ch) {
        if (isprint(ch)) { // || isspace(ch)) {
            switch (ch) {
            case 8: // backspace
            case 12: // Form feed
            case '\n': // newline
            case '\t': // tab
            case '\r': // carriage return
            case '"': // quote
            case '\\': // backslash
            case '\'': // single qoute
                break;
            default:
                printf("%c", ch);
                break;
            }
        }
        ++ch;
    }
    return 0;
}
