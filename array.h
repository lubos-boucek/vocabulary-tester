#include <stdlib.h>
#include <err.h>

struct array {
	size_t n_elements;
	size_t element_size;
	void *address;
};

void new_array(struct array *, size_t);
void *add_elements(struct array *, size_t);
void *get_element(struct array *, int);
size_t get_length(struct array *);
void delete_array(struct array *);

