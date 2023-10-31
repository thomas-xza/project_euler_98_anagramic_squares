#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/file-line-to-int8-array.c"

#define int8   char
#define sint8  signed char
#define uint   unsigned int
#define int64  long long int
#define uint64 unsigned long long int

#define LINES  1786

void
char_count(int8 *line, int8 *total_char_count, int8 *alpha_char_count, int line_n);

int8 alpha_char_count[LINES * 26] = {0};

int8 total_char_count[LINES] = {0};

void
main() {

  int8 line[16] = {0};

  int line_n;

  for ( line_n = 0 ; line_n < LINES ; line_n++ ) {

    file_line_to_int_8_array(&line[0], "98_words.txt", line_n);

    char_count(&line[0], &total_char_count[line_n], &alpha_char_count[line_n * 28], line_n);

    /* printf("%d  %s \n", total_char_count[line_n], line); */

    printf("  %s \n", line);

    memset(line, 0, sizeof(line));

  }
  
}

void
char_count(int8 *line, int8 *total_char_count, int8 *alpha_char_count, int line_n) {

  int8 letter;

  int8 i = 0;

  for ( i = 0 ; i < 16 ; i++ ) {

    if ( (*(line + i) >= 65) &&(*(line + i) <= 90) ) {

      letter = *(line + i) - 64;

      *(total_char_count) += 1;

      printf("%02d  ", letter);

      /* *(alpha_char_count + letter) += 1; */

    }

  }

}
