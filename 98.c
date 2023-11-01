#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./lib/file-line-to-int8-array.c"
#include "./lib/sequential-search-for-n.c"
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
fit_anagram_to_candidates(uint *squares_pt, int *anagram_pairs_pt);

int8
assess_fit(int permutation_a, int permutation_b, int8 *word_a, int8 *word_b);

int8
find_letter_in_string(int8 letter_a, int8 *string);

void
seek_potential_word_fits(int8 *word_a, int8 *word_b, uint *squares_pt);

void
main() {

  int8 total_char_count[LINES] = {0};

  int8 alpha_char_count[LINES * 26] = {0};

  int anagram_pairs[128] = {0};

  uint squares[31624] = {0};

  setup_data(&total_char_count[0], &alpha_char_count[0]);

  find_anagrams(&total_char_count[0], &alpha_char_count[0], &anagram_pairs[0]);

  gen_squares(&squares[0], 31623);

  fit_anagram_to_candidates(&squares[0], &anagram_pairs[0]);

}


void
fit_anagram_to_candidates(uint *squares_pt, int *anagram_pairs_pt) {

  int8 word_a[10] = {0}, word_b[10] = {0};

  int8 pair_selection;

  for (pair_selection = 0; *(anagram_pairs_pt + pair_selection) != 0 ;
       pair_selection += 2) {

    file_line_to_int_8_array(&word_a[0], "98_words.txt", *(anagram_pairs_pt + pair_selection));
  
    file_line_to_int_8_array(&word_b[0], "98_words.txt", *(anagram_pairs_pt + pair_selection + 1));

    printf("%s %s %d\n", word_a, word_b);

    seek_potential_word_fits(&word_a[0], &word_b[0], squares_pt);
  
    memset(word_a, 0, sizeof(word_a));

    memset(word_b, 0, sizeof(word_b));
    
  }

}

void
seek_potential_word_fits(int8 *word_a, int8 *word_b, uint *squares_pt) {

  int i, j, min_sq, max_sq, lower_sq_pos, upper_sq_pos, subset_size, sq_a, sq_b;

  int8 word_a_len, word_b_len, above_this;

  word_a_len = strlen(word_a);

  word_b_len = strlen(word_b);

  min_sq = pow(10,word_a_len - 1);

  max_sq = min_sq * 10;

  lower_sq_pos = binary_search_for_n(min_sq, squares_pt, 31624, 1, &above_this);

  upper_sq_pos = binary_search_for_n(max_sq, squares_pt, 31624, 2, &above_this);

  subset_size = upper_sq_pos - lower_sq_pos;

  /* printf(" %d %d  %d  %d\n", min_sq, max_sq, lower_sq_pos, upper_sq_pos); */

  for (i = 0 ; i < subset_size - 1 ; i++ ) {

    sq_a = *(squares_pt + lower_sq_pos + i);

    for (j = i + 1 ; j < subset_size ; j++ ) {

      sq_b = *(squares_pt + lower_sq_pos + j);

      assess_fit(sq_a, sq_b, word_a, word_b);
      
    }

  }

}


int8
assess_fit(int number_a, int number_b, int8 *word_a, int8 *word_b) {

  int8 letter_a, letter_b, digit_a, digit_b, pos_a, pos_b = 0;

  int8 n_str_a[10], n_str_b[10] = {0};

  int8 cont = 1;

  sprintf(n_str_a, "%d", number_a);

  sprintf(n_str_b, "%d", number_b);

  for ( pos_a = 0 ; n_str_a[pos_a] != '\0' ; pos_a++ ) {

    letter_a = *(word_a + pos_a);

    digit_a = n_str_a[pos_a];

    pos_b = find_letter_in_string(letter_a, word_b);

    digit_b = n_str_b[pos_b];

    /* printf("%c : %c, %c\n", letter_a, digit_a, digit_b); */
    
    if ( digit_a != digit_b ) {

      return -1;

    }

  }

  printf("%s %s\n", n_str_a, n_str_b);

  return 1;

}


int8
find_letter_in_string(int8 letter_a, int8 *string) {

  int8 i;

  for ( i = 0 ; *(string + i) != '\0' ; i++ ) {

    /* printf("find_letter_in_string() %c in %c\n", letter_a, *(string + i)); */

    if ( *(string + i) == letter_a ) {

      return i;

    }

  }

  return -1;

}

void
gen_squares(int *squares, int max) {

  int n = 1;

  uint n_sq = n * n;

  while ( n < max ) {

    *(squares + n) = n_sq;

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

	/* file_line_to_int_8_array(&line_a[0], "98_words.txt", i); */

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
