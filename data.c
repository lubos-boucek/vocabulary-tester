#include <stdio.h>
#include <err.h>
#include <string.h>

#include "common.h"

/* struct entry */

void init_entry(struct entry *e)
{
	e->headword = NULL;
	e->definitions = NULL;
	e->n_definitions = 0;
}

/* update_headword and add_definition trim the newline */
void update_headword(struct entry *e, const char *headword, size_t size)
{
	if ((e->headword = (char *)reallocarray(e->headword, size, sizeof(char))) == NULL) {
		err(1, NULL);
	}

	(void)strlcpy(e->headword, headword, size);
}

void add_definition(struct entry *e, const char *definition, size_t size)
{
	if ((e->definitions = (char **)reallocarray(e->definitions, ++e->n_definitions, sizeof(char *))) == NULL) {
		err(1, NULL);
	}

	if ((e->definitions[e->n_definitions - 1] = (char *)reallocarray(NULL, size, sizeof(char))) == NULL) {
		err(1, NULL);
	}

	(void)strlcpy(e->definitions[e->n_definitions - 1], definition, size);
}

void clear_entry(struct entry *e)
{
	int i;

	free(e->headword);

	for (i = 0; i < e->n_definitions; i++) {
		free(e->definitions[i]);
	}

	free(e->definitions);
	e->n_definitions = 0;
}

/* struct dictionary */

void init_dictionary(struct dictionary *d)
{
	d->entries = NULL;
	d->n_entries = 0;
}

struct entry * add_entry(struct dictionary *d)
{
	if ((d->entries = (struct entry *)reallocarray(d->entries, ++d->n_entries, sizeof(struct entry))) == NULL) {
		err(1, NULL);
	}
	
	init_entry(&d->entries[d->n_entries-1]);

	return &d->entries[d->n_entries-1];
}

void print_dictionary(struct dictionary *d)
{
	int i, j;

	printf("Dictionary contains %d entries:\n\n", (int)d->n_entries);

	for (i = 0; i < d->n_entries; i++) {
		printf("`%s` (%d)\n", d->entries[i].headword, (int)d->entries[i].n_definitions);
		for (j = 0; j < d->entries[i].n_definitions; j++) {
			printf("%s\n", d->entries[i].definitions[j]);
		}
	}
}

void clear_dictionary(struct dictionary *d)
{
	int i;

	for (i = 0; i < d->n_entries; i++) {
		clear_entry(&d->entries[i]);
	}

	free(d->entries);
	d->n_entries = 0;
}
