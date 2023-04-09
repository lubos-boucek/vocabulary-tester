#include <stdio.h>
#include <err.h>
#include <string.h>

#include "common.h"

void
init_entry(struct entry *e)
{
	e->headword = NULL;

	new_array(&e->definitions_array, sizeof(char *));
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

	d = add_elements(&e->definitions_array, 1);

	if ((*d = (char *)reallocarray(NULL, size, sizeof(char))) == NULL) {
		err(1, NULL);
	}

	(void)strlcpy(*d, definition, size);
}

void
print_entry(struct entry *e)
{
	int i;

	printf("`%s` (%lu)\n", e->headword, get_length(&e->definitions_array));

	for (i = 0; i < get_length(&e->definitions_array); i++) {
		printf("\t%s\n", *(char **)get_element(&e->definitions_array, i));
	}
}

void
clear_entry(struct entry *e)
{
	int i;
	char **el;

	free(e->headword);

	for (i = 0; i < get_length(&e->definitions_array); i++) {
		el = get_element(&e->definitions_array, i);
		free(*el);
	}

	delete_array(&e->definitions_array);
}

void
init_dictionary(struct dictionary *d)
{
	new_array(&d->entries_array, sizeof(struct entry));
}

struct entry *
add_entry(struct dictionary *d)
{
	struct entry *e;

	e = add_elements(&d->entries_array, 1);
	init_entry(e);

	return e;
}

void
print_dictionary(struct dictionary *d)
{
	int i;
	struct entry *e;

	printf("Dictionary contains %lu entries_array:\n", get_length(&d->entries_array));

	for (i = 0; i < get_length(&d->entries_array); i++) {
		e = get_element(&d->entries_array, i);

		print_entry(e);
	}
}

void
clear_dictionary(struct dictionary *d)
{
	int i;

	for (i = 0; i < get_length(&d->entries_array); i++) {
		clear_entry(get_element(&d->entries_array, i));
	}

	delete_array(&d->entries_array);
}

char *
find_definition(struct dictionary *d, struct magnifier *m)
{
        struct entry *e;

        e = get_element(&d->entries_array, m->entry_index);

        return *(char **)get_element(&e->definitions_array, m->definition_index);
}

char *
find_headword(struct dictionary *d, size_t index)
{
        struct entry *e;

        e = get_element(&d->entries_array, index);

        return e->headword;
}
