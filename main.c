#include <stdio.h>
#include <stdlib.h>
#include <err.h>

/* TODO: Configurable constants */
const char *file_name = "learners.en.txt";

int
main(int argc, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t line_size = 0;
	ssize_t line_length;

	fp = fopen(file_name, "r");
	
	while ((line_length = getline(&line, &line_size, fp)) != -1) {
		fwrite(line, line_length, 1, stdout);
	}

	free(line);
	if (ferror(fp))
		err(1, "getline");

	fclose(fp);

	return 0;
}
