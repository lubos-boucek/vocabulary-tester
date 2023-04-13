#include <stdio.h>
#include <err.h>
#include <ctype.h>
/* strlcpy */
#include <string.h>
/* isblank */
#include <ctype.h>

#include "common.h"

void
parse_file(struct session *s)
{
	FILE *fp;
	char *line = NULL;
	size_t line_size = 0;
	ssize_t line_length;
	enum parsing_state state = CONTEXT_BETWEEN;
	struct entry *new_entry;
	int def_offset;

	if((fp = fopen(s->data_filename, "r")) == NULL) {
		err(1, "fopen");
	}
	
	while ((line_length = getline(&line, &line_size, fp)) != -1) {
		process_line(line, line_length, &state);
		if (state == CONTEXT_HEADWORD) {
			new_entry = add_entry(&s->dict);
			update_headword(new_entry, line, line_length);
		} else if (state == CONTEXT_ENTRY && (def_offset = is_definition(line)) > -1) {
			add_definition(new_entry, line + def_offset, line_length - def_offset);
		}
	}

	free(line);
	if (ferror(fp))
		err(1, "getline");

	fclose(fp);

	if (s->option_debug) {
		print_dictionary(&s->dict);
	}
}

void
process_line(const char *line, ssize_t line_length, enum parsing_state *state)
{
	int is_blank = 1;
	ssize_t i = 0;
	
	while (i < line_length - 1) {
		if (!isspace(line[i--])) {
			is_blank = 0;
			break;
		}
	}	
/*
 	fwrite(line, line_length, 1, stdout);
*/
	if (*state == CONTEXT_BETWEEN && !is_blank) {
		*state = CONTEXT_HEADWORD;
	} else if (!is_blank) {
		*state = CONTEXT_ENTRY;
	} else {
		*state = CONTEXT_BETWEEN;
	}
}

/*	-1 : false
	or : starting position */
int
is_definition(const char *line)
{
	int i;
/*
	int digits = 1;
*/
	for (i = 0; line[i]; i++) {
		if (isblank(line[i]))
			continue;
		if (line[i] == ':' || isdigit(line[i]))
			return i;
/*
		else if (isdigit(line[i])) {
			while (isdigit(line[i + 1]))
				i++;
		}
*/
	}

	return -1;
}
