
/* file_row_to_array_of_ints(&rows[i].c[0], "./lib/83-martix.tx", i);
*/

void file_row_to_array_of_ints(int *ints_init_ptr, char *filename, int row);

void file_row_to_array_of_ints(int *ints_init_ptr, char *filename, int row) {

  FILE *ints_file;

  int* ints_ptr = ints_init_ptr;

  int i = 0;

  char ch, number[10];

  char line[1024];

  ch = 0;

  if ((ints_file = fopen(filename, "r"))) {

    /* printf("opened file\n"); */

    if ( row != 0 ) {

      ch = fgetc(ints_file);

    }

    while ( i != row && ch != EOF ) {

      ch = fgetc(ints_file);

      /* printf("%c : %d\n", ch, ch); */
      
      if ( ch == 10 ) {

	i++;

      }

      if ( i == row ) {

	break;

      }

    }

    if ( i == row ) {

      ch = 0;

      while ( ch != 10 ) {

	fscanf(ints_file, "%d", ints_ptr);

	/* printf("%d \n", *ints_ptr); */

	ints_ptr++;

	ch = fgetc(ints_file);

	/* printf("found char: %d\n", ch); */

      }

    }
    
    fclose(ints_file);

    *ints_ptr = '\0';

    /* printf("read ints from file at line %d, to %p \n", row, ints_init_ptr); */

  }

}
