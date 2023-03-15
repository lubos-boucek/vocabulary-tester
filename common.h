#include <stdlib.h>

/* session.h */

struct session {
	char *config_filename;
	char *data_filename;
};

void init_session(struct session *);
void process_args(struct session *, int, char **);
void read_config(struct session *);

/* data.h */

struct entry {
	char *headword;
	char **definitions;
	size_t n_definitions;
};

struct dictionary {
	struct entry *entries;
	size_t n_entries;
};

void init_entry(struct entry *);
void add_definition(struct entry *);
void clear_entry(struct entry *);

void init_dictionary(struct dictionary *);
void clear_dictionary(struct dictionary *);

/* parse.h */

enum parsing_state {BETWEEN, HEADWORD, ENTRY};

void read_data(struct session *);
void process_line(const char *, ssize_t, enum parsing_state *);
