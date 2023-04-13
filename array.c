#include "array.h"

void
new_array(struct array *a, size_t s)
{
	a->n_elements = 0;
	a->element_size = s;
	a->address = NULL;
}

void *
add_elements(struct array *a, size_t n)
{
	if ((a->address = reallocarray(a->address, a->n_elements + n, \
a->element_size)) == NULL) {
                err(1, NULL);
        }

	a->n_elements += n;

	return a->address + a->element_size * (a->n_elements - n);
}

void *
get_element(const struct array *a, size_t p)
{
	if (p > a->n_elements - 1)
		return NULL;

	return a->address + a->element_size * p;
}

size_t
get_length(const struct array *a)
{
	return a->n_elements;
}

void
delete_array(struct array *a)
{
	free(a->address);
	a->n_elements = 0;
}
