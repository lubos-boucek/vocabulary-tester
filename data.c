#include <stdio.h>
#include <err.h>
#include <string.h>

#include "common.h"

/* struct entry */

void
init_entry(struct entry *e)
{
	e->headword = NULL;

	new_array(&e->array_definitions, sizeof(char *));
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
	char **d;

	d = add_elements(&e->array_definitions, 1);

	if ((*d = (char *)reallocarray(NULL, size, sizeof(char))) == NULL) {
		err(1, NULL);
	}

	(void)strlcpy(*d, definition, size);
}

void
print_entry(struct entry *e)
{
	int i;

	printf("`%s` (%d)\n", e->headword, (int)get_length(&e->array_definitions));

	for (i = 0; i < get_length(&e->array_definitions); i++) {
		printf("\t%s\n", *(char **)get_element(&e->array_definitions, i));
	}
}

void
clear_entry(struct entry *e)
{
	int i;
	char **el;

	free(e->headword);

	for (i = 0; i < get_length(&e->array_definitions); i++) {
		el = get_element(&e->array_definitions, i);
		free(*el);
	}

	delete_array(&e->array_definitions);
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
	int i;
	struct entry *e;

	printf("Dictionary contains %d entries:\n", (int)get_length(&d->array_entries));

	for (i = 0; i < get_length(&d->array_entries); i++) {
		e = get_element(&d->array_entries, i);

		print_entry(e);
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
