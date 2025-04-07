/**
 * @brief Detect adjacent identical words in its input.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <assert.h>

_Thread_local unsigned long lineno;


/**
 * @brief Reads the next word from an opened file into
 * @a buf[0 .. size-1].
 *
 * @returns  0   when EOF is reached
 * @returns  1   after reading the next word into @c buf
 */
int get_word(FILE *restrict, size_t size, char [size+1]);

/**
 * @brief Reads each word, compares it with the previous
 * word, and complains about duplicates.
 */
void double_word(char *, FILE *restrict);


int get_word(FILE *restrict fp, size_t size, char buf[size+1])
{
    assert(size);

    int c = getc(fp);
    for (; c != EOF && isspace(c); c = getc(fp)) {
        if (c == '\n')
            lineno++;
    }

    size_t i = 0;
    for (; c != EOF && !isspace(c); c = getc(fp)) {
        if (i < size-1)
            buf[i++] = tolower(c);
    }
    if (i < size) {
        buf[i] = '\0';
    }

    if (c != EOF) {
        ungetc(c, fp);
    }
    return (buf[0] != '\0');
}

void double_word(char *name, FILE *restrict fp)
{
    assert(fp);
    
    enum { N = 128, };
    char prev[N];
    char word[N];

    lineno = 1;
    prev[0] = '\0';
    for (; get_word(fp, sizeof word, word);) {
        if (isalpha(word[0]) && !strcmp(prev, word)) {
            if (name)
                fprintf(stdout, "%s:", name);

            fprintf(stdout, "%lu: %s\n", lineno, word);
        }

        strcpy(prev, word);
    }
}


int main(int argc, char *argv[argc + 1])
{
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            fprintf(stderr, "%s: can't open '%s' (%s)", argv[0], argv[i], strerror(errno));
            errno = EXIT_SUCCESS;
            return EXIT_FAILURE;
        }
        else {
            double_word(argv[i], fp);
            fclose(fp);
        }
    }

    if (argc == 1) {
        double_word((void *) 0, stdin);
    }

    return EXIT_SUCCESS;
}
