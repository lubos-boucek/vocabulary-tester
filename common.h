#include <stdlib.h>

struct entry {
	char *headword;
	char **definitions;
	size_t n_definitions;
};

struct dictionary {
	struct entry *entries;
	size_t n_entries;
};

struct session {
	char *config_filename;
	char *data_filename;
	struct dictionary dict;
};

/* session.h */

void init_session(struct session *);
void process_args(struct session *, int, char **);
void read_config(struct session *);
void clear_session(struct session *);

/* data.h */

void init_entry(struct entry *);
void add_definition(struct entry *);
void clear_entry(struct entry *);

void init_dictionary(struct dictionary *);
void print_headwords(struct dictionary *);
struct entry * add_entry(struct dictionary *);
void clear_dictionary(struct dictionary *);

/* parse.h */

enum parsing_state {BETWEEN, HEADWORD, ENTRY};

void parse_file(struct session *);
void process_line(const char *, ssize_t, enum parsing_state *);
