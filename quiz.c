#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void
init_questionnaire(struct questionnaire *q)
{
	q->entries_count = 0;
	new_array(&q->magnifiers_array, sizeof(struct magnifier));
}

void
build_questionnaire(struct questionnaire *q, const struct dictionary *d)
{
        int i, j;
        struct entry *e;
        struct magnifier *l;
        size_t definitions_count;

        for (i = 0; i < get_length(&d->entries_array); i++) {
                e = get_element(&d->entries_array, i);

                definitions_count = get_length(&e->definitions_array);
                if (definitions_count < 1)
                        continue;
                q->entries_count++;

                for (j = 0; j < definitions_count; j++) {
                        l = add_elements(&q->magnifiers_array, 1);
                        l->entry_index = i;
                        l->definition_index = j;
                }
        }
}

void
print_questionnaire(const struct questionnaire *q)
{
        int i;
        struct magnifier *l;

        for (i = 0; i < get_length(&q->magnifiers_array); i++) {
                l = get_element(&q->magnifiers_array, i);
                printf("[%lu ; %lu] at %p\n", l->entry_index, l->definition_index, l);
        }

        printf("count of definitions = %lu, count of entries = %lu\n", get_length(&q->magnifiers_array), q->entries_count);
}

void
clear_questionnaire(struct questionnaire *q)
{
	delete_array(&q->magnifiers_array);
	q->entries_count = 0;
}

/* TODO: proper handling of not found case */
/* Returns the entry_index of the `rank`th entry (ordered non-empty entries in magnifiers_array). */
size_t
which_entry(struct questionnaire *q, uint32_t rank)
{
	size_t i, prev_entry_index;
	uint32_t r = 0;
	struct magnifier *dp;
	
	for (i = 0; i < get_length(&q->magnifiers_array); i++) {
		dp = get_element(&q->magnifiers_array, i);

		if (i && dp->entry_index != prev_entry_index)
			r++;

		if (rank == r)
			return dp->entry_index;

		prev_entry_index = dp->entry_index;
	}

	return 0;
}

/* Assumes that items of the same entry are adjacent in magnifiers_array.
   Randomly picks a definition of the entry at `index`. */
struct magnifier *
pick_definition(struct questionnaire *q, size_t index)
{
	int found = 0;
	size_t i;
	struct magnifier *dp, *start = NULL;
	uint32_t r;

	for (i = 0; i < get_length(&q->magnifiers_array); i++) {
		dp = get_element(&q->magnifiers_array, i);

		if (dp->entry_index == index) {
			if (!found)
				start = dp;
			found++;
		}
	}

	r = arc4random_uniform(found);

	return start + r;
}
