// gcc make_pathname.c  -pedantic -Wall -Wextra -Wconversion -fsanitize=undefined,address -g -O0

// You can assume the following headers have already been included: stdio.h,
// stdlib.h, limits.h, ctype.h, stdbool.h, stdint.h, and string.h.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define SLASH_LEN 1
#define DOT_LEN 1
#define NULL_LEN 1
#define SUM_LEN (SLASH_LEN + DOT_LEN + NULL_LEN)

void fill_buffer(
    const char *dir, size_t dirlen, const char *fname, size_t filelen,
    const char *ext, size_t extlen, char *path)
{
    memcpy(path, dir, dirlen);
    path[dirlen] = '/';
    memcpy(path + dirlen + SLASH_LEN, fname, filelen);
    path[dirlen + SLASH_LEN + filelen] = '.';
    memcpy(path + dirlen + SLASH_LEN + filelen + DOT_LEN, ext, extlen);
    path[dirlen + SLASH_LEN + filelen + DOT_LEN + extlen] = '\0';
}

/** Return true when the sum of dirlen, filelen, extlen and 3
 * would exceed the maximum possible value of a size_t; otherwise,
 * return false.
 */
bool would_wrap_around(size_t dirlen, size_t filelen, size_t extlen)
{
    return (SUM_LEN + dirlen + filelen < filelen             //
            || SUM_LEN + dirlen + filelen < dirlen           //
            || SUM_LEN + filelen + extlen < extlen           //
            || SUM_LEN + filelen + extlen < filelen          //
            || SUM_LEN + dirlen + extlen < dirlen            //
            || SUM_LEN + dirlen + extlen < extlen            //
            || SUM_LEN + dirlen + extlen + filelen < dirlen  //
            || SUM_LEN + dirlen + extlen + filelen < filelen //
            || SUM_LEN + dirlen + extlen + filelen < extlen  //
    );
}

// Concatenates dir, fname and ext, with a forward slash ('/') between dir and
// fname and a full stop ('.') between fname and ext.
//
// The return value is normally a pointer to dynamically allocated memory
// containing this concatenated string, which should be freed by the caller
// after use.
//
// If, however, the system cannot allocate sufficient memory to hold the
// resulting string, then a NULL pointer is returned.
//
// Each of dir, fname and ext must be valid null-terminated strings;
// furthermore, the fname and ext parameters must not contain any forward-slash
// or full stop characters. If any of these conditions do not hold, the result
// of calling the function is undefined.
char *make_pathname(const char *dir, const char *fname, const char *ext)
{
    size_t dirlen = strlen(dir);
    size_t filelen = strlen(fname);
    size_t extlen = strlen(ext);
    if (would_wrap_around(dirlen, filelen, extlen))
        return NULL;
    char *path = malloc(dirlen + SLASH_LEN + filelen + DOT_LEN + extlen + NULL_LEN);
    if (path == NULL)
        return NULL; // malloc() failed. Do not continue.
    fill_buffer(dir, dirlen, fname, filelen, ext, extlen, path);
    return path;
}

int main()
{
    char *c = make_pathname("ddddddddddddd", "ff", "xx");
    printf("%s", c);
    free(c);

    // TEST WRAP CHECK
    // size_t dirlen = 18446744073709551595UL;
    // size_t filelen = 9;
    // size_t extlen = 16;
    // bool res = would_wrap_around(dirlen, filelen, extlen);
    // printf("%d\n", res);
}