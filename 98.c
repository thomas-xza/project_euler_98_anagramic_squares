#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/file-line-to-int8-array.c"
#include "./lib/binary-search-for-n.c"

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
find_anagrams(int8 *total_char_count, int8 *alpha_char_count, int *anagram_pairs);

int8
compare_char_counts(int8 *char_count_a, int8 *char_count_b);

void
gen_squares(int *squares, int max);

void
attempt_permutations(int8 *filename_pt, int *squares_pt);

void
main() {

  int8 total_char_count[LINES] = {0};

  int8 alpha_char_count[LINES * 26] = {0};

  int anagram_pairs[128] = {0};

  uint squares[31623] = {0};

  /* setup_data(&total_char_count[0], &alpha_char_count[0]); */

  /* find_anagrams(&total_char_count[0], &alpha_char_count[0], &anagram_pairs[0]); */

  gen_squares(&squares[0], 31623);

  attempt_permutations("9_unique_digit_permutations.tx", &squares[0]);

}

void
attempt_permutations(int8 *filename_pt, int *squares_pt) {

  uint line_n, n, pos;

  int8 above_this;

  int8 line[10] = {0};

  for ( line_n = 10013 ; line_n < 362879 ; line_n++ ) {
    
    memset(line, 0, sizeof(line));

    file_line_to_int_8_array(&line[0], filename_pt, line_n);

    n = atoi(&line[0]);

    /* printf("%d\n", n); */

    pos = binary_search_for_n(n, squares_pt, 31623, 0, &above_this);

    if ( pos != -1 ) {

      printf("%d", n);

    }

  }

}

void
gen_squares(int *squares, int max) {

  int n = 1;

  uint n_sq = n * n;

  while ( n < max ) {

    squares[n] = n_sq;

    /* printf("%d  %d\n", n, n_sq); */

    n += 1;

    n_sq = n * n;

  }

}

void
find_anagrams(int8 *total_char_count, int8 *alpha_char_count, int *anagram_pairs) {

  int i, j, a = 0;

  int8 anagram_chk, anagram_pair;

  /* int8 line_a[16], line_b[16] = {0}; */

  for ( i = 0 ; i < LINES - 1 ; i++ ) {

    for ( j = i + 1 ; j < LINES ; j++ ) {

      anagram_chk = 0;

      anagram_pair = 0;

      if ( *(total_char_count + i) == *(total_char_count + j) ) {

	anagram_chk = 1;

      }

      if ( anagram_chk == 1 ) {

	anagram_pair = \
	  compare_char_counts(alpha_char_count + i * 26, alpha_char_count + j * 26);

      }

      if ( anagram_pair == 1 ) {

	*(anagram_pairs + a) = i;

	*(anagram_pairs + a + 1) = j;

	a += 2;

	/* memset(line_a, 0, sizeof(line_a)); */

	/* memset(line_b, 0, sizeof(line_b)); */

	/* file_line_to_int_8_array(&line_a[0], "98_words.txt", i);	 */

	/* file_line_to_int_8_array(&line_b[0], "98_words.txt", j); */

	/* printf("%s %s \n", line_a, line_b); */

      }
      
    }

  }  

}

int8
compare_char_counts(int8 *char_count_a, int8 *char_count_b) {

  int8 i;

  for ( i = 0 ; i < 26 ; i++ ) {

    if ( *(char_count_a + i) != *(char_count_b + i) ) {

	return 0;

    }

  }

  return 1;

}

void
setup_data(int8 *total_char_count, int8 *alpha_char_count) {

  int8 line[16] = {0};

  int line_n;

  for ( line_n = 0 ; line_n < LINES ; line_n++ ) {

    file_line_to_int_8_array(&line[0], "98_words.txt", line_n);

    char_count(&line[0], total_char_count + line_n, alpha_char_count + line_n * 26, line_n);

    /* print_char_count_quantities((alpha_char_count + line_n * 26)); */

    /* printf("  %d  %s \n\n", total_char_count[line_n], line); */

    memset(line, 0, sizeof(line));

  }
  
}

void
print_char_count_quantities(int8 *alpha_char_count) {

  int8 i;

  /* printf("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\n"); */

  for ( i = 0 ; i < 26 ; i++ ) {

    printf("%d ", *(alpha_char_count + i));

  }

  printf("\n");

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
