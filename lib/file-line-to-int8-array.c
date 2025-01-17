
/* 

  provide an array, filename, and line target number to the function, and it will fill the array

  note: file must end with newline

  file_line_to_int_8_array(&line_data[0], "./lib/83-martix.tx", line_target);

*/

#define int8 char



void file_line_to_int_8_array(int8 *line_data_pt, char *filename, int line_target);

void file_line_to_int_8_array(int8 *line_data_pt, char *filename, int line_target) {

  FILE *data_file;

  int line_n = 0;

  int8 ch = 0;

  size_t pos = 0;

  if ((data_file = fopen(filename, "r"))) {

    /* printf("opened file\n"); */

    if ( line_target != 0 ) {

      ch = fgetc(data_file);

    }

    while ( line_n != line_target ) {

      /*  this while loop iterates line_n & pos to target line_target  */

      ch = fgetc(data_file);

      if ( ch == 10 ) {

	line_n++;

      }

      if ( line_n == line_target ) {

	/* printf("line_n: %d\n", line_n); */

	break;

      }

    }

    if ( line_n == line_target ) {

      ch = fgetc(data_file);

      while ( ch != 10 ) {

	*(line_data_pt + pos) = ch;
	
      	pos++;

	ch = fgetc(data_file);

      	/* printf("found char at #%d: %c\n", pos, ch); */

      }

      /* *(line_data_pt + pos) = '\0'; */

    }
    
    fclose(data_file);

    /* printf("read ints from file at line_target %d, to %p \n", line_target, line_data_pt); */

  }

}
