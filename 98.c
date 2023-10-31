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
setup_data(int8 *total_char_count, int8 *alpha_char_count);

void
char_count(int8 *line, int8 *total_char_count, int8 *alpha_char_count, int line_n);

void
print_char_count_quantities(int8 *alpha_char_count);

void
main() {

  int8 total_char_count[LINES] = {0};

  int8 alpha_char_count[LINES * 26] = {0};

  setup_data(&total_char_count[0], &alpha_char_count[0]);

}

void
setup_data(int8 *total_char_count, int8 *alpha_char_count) {

  int8 line[16] = {0};

  int line_n;

  for ( line_n = 0 ; line_n < LINES ; line_n++ ) {

    file_line_to_int_8_array(&line[0], "98_words.txt", line_n);

    char_count(&line[0], (total_char_count), (alpha_char_count + line_n * 26), line_n);

    print_char_count_quantities((alpha_char_count + line_n * 26));

    printf("  %d  %s \n\n", total_char_count[line_n], line);

    memset(line, 0, sizeof(line));

  }
  
}

void
print_char_count_quantities(int8 *alpha_char_count) {

  int8 i;

  printf("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\n");

  for ( i = 0 ; i < 26 ; i++ ) {

    printf("%d ", *(alpha_char_count + i));

  }

}

void
char_count(int8 *line, int8 *total_char_count, int8 *alpha_char_count, int line_n) {

  int8 letter;

  int8 i = 0;

  for ( i = 0 ; i < 16 ; i++ ) {

    if ( (*(line + i) >= 65) &&(*(line + i) <= 90) ) {

      *(total_char_count) += 1;

      letter = *(line + i) - 65;

      /* printf("%02d  ", letter); */

      *(alpha_char_count + letter) += 1;

    }

  }

}
