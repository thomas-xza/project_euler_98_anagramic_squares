
#define uint unsigned int
#define uint64 unsigned long long int

int
sequential_search_for_n(int n, uint *set_pt, int init_pos, char *found);

int
sequential_search_for_n_int_64(uint64 n, uint64 *set_pt, int init_pos);

int
sequential_search_for_n(int n, uint *set_pt, int init_pos, char *found) {

  /*  If iterating through a sequential set of values, then init_pos
      should be position within set[] of last found n.
  */

  int i = init_pos;

  set_pt = set_pt + init_pos;

  /*  Null terminated set[] expected.  */

  while ( *set_pt != '\0' ) {

    if ( n == *set_pt ) {

      /*  If found, return the position of this n.  */

      *found = 1;
	
      return i;

    }

    if ( n < *set_pt ) {

      /*  set[] is expected to be sorted, low to high. So, if the
	  value in the set is larger than n, then n cannot be in
	  the set.  Return the position 1 before the set values
	  are larger.   */

      *found = 0;
	
      return i - 1;

    }

    /*  Keep track of position within the array without doing
	pointer arithmetic.  */

    i++;

    set_pt++;

  }

  *found = 0;

  return -1;

}


int
sequential_search_for_n_int_64(uint64 n, uint64 *set_pt, int init_pos) {

  int i = init_pos;

  set_pt = set_pt + init_pos;

  /*  Null terminated set[] expected.  */

  while ( *set_pt != '\0' ) {

      if ( n == *set_pt ) {

	/*  If found, return the position of n.  */
	
	return i;

      }

      if ( n < *set_pt ) {

	/*  set[] is expected to be sorted, low to high. So, if the
	      value in the set is larger than n, then n cannot be in
	      the set.  Return the position where the last set value
	      is lower.  */
	
	return i - 1;

      }

      /*  Keep track of position within the array without doing
	  pointer arithmetic.  */

      i++;

      set_pt++;

    }

  return -1;

}
