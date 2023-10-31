
#define uint      unsigned int
#define uint64    unsigned long long int

#define INT_SIZE  uint

int
binary_search_for_n(INT_SIZE n, INT_SIZE *array_pt, int len, char return_pos_always, char *above_this);

/*
  `len` is quantity of all values, not position of last value.
  (Often `len` is equal to array size).
  int8 example[len];
  binary_search_for_n(_, _, position_of_last_value + 1, _, _);

  `return_pos_always` is about whether the function should return a
  closest match, or -1 if not found.

  `above_this` is related to above - return position of closest match
  above or below the target to search for.
*/
  

int
binary_search_for_n(INT_SIZE n, INT_SIZE *set_pt, int len, char return_pos_always, char *above_this) {

  int mid_pos = len / 2;

  int lower_bound = 0;

  int upper_bound = len - 1;

  INT_SIZE focus = *(set_pt + mid_pos); 

  INT_SIZE focus_above = *(set_pt + mid_pos + 1);

  char end = 0;

  while (1) {

    if ( focus == n ) {

      *above_this = 0;

      return mid_pos;

    } else if ( focus_above == n ) {

      *above_this = 0;

      return mid_pos + 1;

    } else if ( lower_bound + 1 == upper_bound ) {
      
      if ( return_pos_always == 2 ) {

	*above_this = -1;

	return upper_bound;

      } else if ( return_pos_always == 1 ) {

	*above_this = 1;

	return lower_bound;

      }
      
      return -1;

    } else if ( n > focus ) {

      lower_bound = mid_pos;

    } else if ( n < focus ) {

      upper_bound = mid_pos;

    }

    mid_pos = lower_bound + (upper_bound - lower_bound) / 2;

    focus = *(set_pt + mid_pos);

    focus_above = *(set_pt + mid_pos + 1);

    /* printf("lower_bound: %d\n", lower_bound); */

    /* printf("upper_bound: %d\n", upper_bound); */

    /* printf("mid_pos: %d\n", mid_pos); */

    /* printf("focus: %lld\n", focus); */

    /* printf("focus_above: %lld\n\n", focus_above); */

  }

}
