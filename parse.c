#include <stdio.h>
#include <err.h>
#include <ctype.h>

#include "common.h"

void read_data(struct session *s)
{
	FILE *fp;
	char *line = NULL;
	size_t line_size = 0;
	ssize_t line_length;
	enum parsing_state state = BETWEEN;

	fp = fopen(s->data_filename, "r");
	
	while ((line_length = getline(&line, &line_size, fp)) != -1) {
		process_line(line, line_length, &state);
	}

	free(line);
	if (ferror(fp))
		err(1, "getline");

	fclose(fp);
}

void process_line(const char *line, ssize_t line_length, enum parsing_state *state)
{
	int is_blank = 1;
	ssize_t i = 0;
	
	while (i < line_length - 1) {
		if (!isspace(line[i--])) {
			is_blank = 0;
			break;
		}
	}	

 	fwrite(line, line_length, 1, stdout);

	if (*state == BETWEEN && !is_blank) {
		*state = HEADWORD;
	} else if (!is_blank) {
		*state = ENTRY;
	} else {
		*state = BETWEEN;
	}
}
