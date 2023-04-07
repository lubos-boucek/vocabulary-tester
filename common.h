#include <stdlib.h>
#include "array.h"

struct entry {
	char *headword;

	struct array definitions;
};

struct dictionary {
	struct array entries;
};

struct session {
	char *config_filename;
	char *data_filename;
	struct dictionary dict;
	int quiz_options;
	int quiz_questions;
};

/* session.h */

void init_session(struct session *);
void process_args(struct session *, int, char **);
void read_config(struct session *);
void clear_session(struct session *);

/* data.h */

void init_entry(struct entry *);
void update_headword(struct entry *, const char *, size_t);
void add_definition(struct entry *, const char *, size_t);
void print_entry(struct entry *);
void clear_entry(struct entry *);

void init_dictionary(struct dictionary *);
struct entry *add_entry(struct dictionary *);
void print_dictionary(struct dictionary *);
void clear_dictionary(struct dictionary *);

/* parse.h */

enum parsing_state {BETWEEN, HEADWORD, ENTRY};

void parse_file(struct session *);
void process_line(const char *, ssize_t, enum parsing_state *);
int is_definition(const char *);
