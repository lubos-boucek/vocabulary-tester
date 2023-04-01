#include <stdio.h>
#include <err.h>
#include <string.h>

#include "common.h"

/* struct entry */

void
init_entry(struct entry *e)
{
	e->headword = NULL;
	e->definitions = NULL;
	e->n_definitions = 0;
}

/* CAVE: update_headword and add_definition trim the newline */

void
update_headword(struct entry *e, const char *headword, size_t size)
{
	if ((e->headword = (char *)reallocarray(e->headword, size, sizeof(char))) == NULL) {
		err(1, NULL);
	}

	(void)strlcpy(e->headword, headword, size);
}

void
add_definition(struct entry *e, const char *definition, size_t size)
{
	if ((e->definitions = (char **)reallocarray(e->definitions, ++e->n_definitions, sizeof(char *))) == NULL) {
		err(1, NULL);
	}

	if ((e->definitions[e->n_definitions - 1] = (char *)reallocarray(NULL, size, sizeof(char))) == NULL) {
		err(1, NULL);
	}

	(void)strlcpy(e->definitions[e->n_definitions - 1], definition, size);
}

void
clear_entry(struct entry *e)
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

void
init_dictionary(struct dictionary *d)
{
	new_array(&d->array_entries, sizeof(struct entry));
}

struct entry *
add_entry(struct dictionary *d)
{
	struct entry *e;

	e = add_elements(&d->array_entries, 1);
	init_entry(e);

	return e;
}

void
print_dictionary(struct dictionary *d)
{
	int i, j;
	struct entry *e;

	printf("Dictionary contains %d entries:\n\n", (int)get_length(&d->array_entries));

	for (i = 0; i < get_length(&d->array_entries); i++) {
		e = get_element(&d->array_entries, i);

		printf("`%s` (%d)\n", e->headword, (int)e->n_definitions);
		for (j = 0; j < e->n_definitions; j++) {
			printf("%s\n", e->definitions[j]);
		}
	}
}

void
clear_dictionary(struct dictionary *d)
{
	int i;

	for (i = 0; i < get_length(&d->array_entries); i++) {
		clear_entry(get_element(&d->array_entries, i));
	}

	delete_array(&d->array_entries);
}
