#include <stdio.h>
#include <err.h>

#include "common.h"

void init_entry(struct entry *e)
{
	e->headword = NULL;
	e->definitions = NULL;
	e->n_definitions = 0;
}

void add_definition(struct entry *e)
{

}

void clear_entry(struct entry *e)
{
	free(e->headword);

/* TODO: free all */
	free(e->definitions);
	e->n_definitions = 0;
}

void init_dictionary(struct dictionary *d)
{
	d->entries = NULL;
	d->n_entries = 0;
}

void print_headwords(struct dictionary *d)
{
	int i;

	printf("The dictionary contains %u headwords:\n", (int)d->n_entries);

	for (i = 0; i < d->n_entries; i++) {
		if (d->entries[i].headword != NULL)
			printf("%s", d->entries[i].headword);
	}
}

struct entry * add_entry(struct dictionary *d)
{
	if ((d->entries = reallocarray(d->entries, ++d->n_entries, sizeof(struct entry))) == NULL) {
		err(1, NULL);
	}
	
	init_entry(&d->entries[d->n_entries-1]);

	return &d->entries[d->n_entries-1];
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
