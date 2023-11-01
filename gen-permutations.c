#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void
gen_last_combination(char *char_range, int char_range_len, char *target_perm, int target_perm_len);

void
iterate_permutation(char *char_range, int char_range_len, char *perm, int perm_len);

char
roll_char_at_position(char *char_range, int char_range_len, char *perm, int perm_len, int perm_pos);

char
check_if_permutation(char *perm_init, char *perm, int perm_len);


int
main() {

  char char_range[64] = "123456789";

  char perm_init[32] = "12345678";

  char perm[32];

  strcpy(perm, perm_init);

  char target_perm[32];

  char permutation = 0;

  int char_range_len = strlen(char_range);

  int perm_len = strlen(perm_init);

  gen_last_combination(&char_range[0], char_range_len, &target_perm[0], perm_len);

  printf("%s\n", perm);

  printf("%s\n", target_perm);

  while (strcmp(perm, target_perm) != 0 ) {

    iterate_permutation(&char_range[0], char_range_len, &perm[0], perm_len);

    permutation = check_if_permutation(&perm_init[0], &perm[0], perm_len);

    if ( permutation == 1 ) {

      printf("%s\n", perm);

    } 

  }
  
  return 0;

}


void
gen_last_combination(char *char_range, int char_range_len, char *target_perm, int target_perm_len) {

  char last_char = *(char_range + char_range_len - 1);

  char i;

  for ( i = 0 ; i < target_perm_len ; i++ ) {

    *(target_perm + i) = last_char;

  }

  *(target_perm + target_perm_len) = '\0';

}


void
iterate_permutation(char *char_range, int char_range_len, char *perm, int perm_len) {

  int i, focus;

  char change_more = 0;

  change_more = roll_char_at_position(char_range, char_range_len, perm, perm_len - 1, perm_len - 1);

  focus = 2;

  while ( change_more == 1 ) {

    /* printf("need to change another\n"); */

    change_more = roll_char_at_position(char_range, char_range_len, perm, perm_len, perm_len - focus);

    focus++;

  }

}


char
roll_char_at_position(char *char_range, int char_range_len, char *perm, int perm_len, int perm_pos) {

  /*  given a permutation, and a set of chars to permutate,
      select the position provided, find the next in the set of chars
      and adjust it, returning a flag if this should cause a
      chain reaction
  */

  char i, j;

  char *char_range_pt = char_range;

  char *perm_pt = perm + perm_pos;

  char char_range_last = *(char_range + char_range_len);

  char change_two_chars = 0;

  for ( i = 0 ; i < char_range_len ; i++ ) {

    if ( *perm_pt == *char_range_pt ) {

      char_range_pt++;

      break;

    } else {

      char_range_pt++;

    }

  }

  if ( i == char_range_len - 1 ) {

    char_range_pt = char_range;

    change_two_chars = 1;

  }

  *perm_pt = *char_range_pt;

  return change_two_chars;
  
  /* printf("char_range_pt: %c\n", *char_range_pt); */

  /* printf("perm_pt: %c\n", *perm_pt); */

}

char
check_if_permutation(char *perm_init, char *perm, int perm_len) {

  char ascii_range[128];

  char ascii_perm[128];

  memset(ascii_range, 0, 128);

  memset(ascii_perm, 0, 128);

  char char_select;

  int i;

  for ( i = 0 ; i < perm_len ; i++ ) {

    char_select = *(perm + i);

    ascii_perm[char_select]++;

    char_select = *(perm_init + i);

    ascii_range[char_select]++;

  }

  for ( i = 48 ; i < 123 ; i++ ) {

    if ( ascii_range[i] != ascii_perm [i] ) {

      return 0;

    }

  }

  return 1;

}
