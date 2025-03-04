/// @file
/// @brief The test code for the debmalloc. 
/// @copyright
///   2025 Mitsutoshi Nakano
///   SPDX-License-Identifier: Apache-2.0
/// @author Mitsutoshi Nakano <ItSANgo@gmail.com>
/// @version 0.1.0
/// @date 2025-03-04

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "debmalloc.h"

#define MESSAGE "Hello, World!"
#define PART_MESSAGE "Hel"
#define PART_MESSAGE_LENGTH 3

int
main(void)
{
    char *p = malloc(1024);
    char *q = realloc(p, 2048);
    free(q);
    p = calloc(1, 1024);
    free(p);
    p = strdup(MESSAGE);
    assert(strcmp(p, MESSAGE) == 0);
    free(p);
    p = strndup(MESSAGE, PART_MESSAGE_LENGTH);
    assert(strcmp(p, PART_MESSAGE) == 0);
    free(p);
    
    exit(0);
}
