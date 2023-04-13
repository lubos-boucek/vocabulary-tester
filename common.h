#include <stdlib.h>

#include "compat/common.h"
#include "array.h"

struct entry {
	char *headword;

	/* array of char * */
	struct array definitions_array;
};

void init_entry(struct entry *);
void update_headword(struct entry *, const char *, size_t);
void add_definition(struct entry *, const char *, size_t);
/* debugging function */
void print_entry(struct entry *);
void clear_entry(struct entry *);

struct dictionary {
	struct array entries_array;
};

/* Coordinates for accessing a definition in `struct dictionary`. */
struct magnifier {
	size_t entry_index;
	size_t definition_index;
};

void init_dictionary(struct dictionary *);
struct entry *add_entry(struct dictionary *);
/* debugging function */
void print_dictionary(struct dictionary *);
void clear_dictionary(struct dictionary *);

char *find_headword(struct dictionary *, size_t);
char *find_definition(struct dictionary *, struct magnifier *);

/* Extends an existing dictionary, should be rebuilt after any change. */
struct questionnaire {
	/* array of `struct magnifier` */
	struct array magnifiers_array;

	/* non-empty entries */
	size_t entries_count;
};

/* TODO: check for repeated builds */
void init_questionnaire(struct questionnaire *);
void build_questionnaire(struct questionnaire *, const struct dictionary *);
/* debugging function */
void print_questionnaire(const struct questionnaire *);
void clear_questionnaire(struct questionnaire *);

size_t which_entry(struct questionnaire *, uint32_t);
struct magnifier *pick_definition(struct questionnaire *, size_t);

/* session.h */

struct session {
	char *config_filename;
	char *data_filename;

	struct dictionary dict;
	struct questionnaire quest;

	unsigned long quiz_options;
	unsigned long quiz_questions;
};

enum question_type {DEFINITION, HEADWORD};

unsigned generate_question(struct session *, enum question_type, unsigned);
unsigned generate_definition_question(struct session *s, unsigned n_options);
unsigned generate_headword_question(struct session *s, unsigned n_options);

void init_session(struct session *);
void process_args(struct session *, int, char **);
void validate_args(struct session *);
void read_config(struct session *);
void start_session(struct session *);
void ask_questions(struct session *);
void clear_session(struct session *);

/* parse.h */

enum parsing_state {CONTEXT_BETWEEN, CONTEXT_HEADWORD, CONTEXT_ENTRY};

void parse_file(struct session *);
void process_line(const char *, ssize_t, enum parsing_state *);
int is_definition(const char *);
