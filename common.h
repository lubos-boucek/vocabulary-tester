#include <stdlib.h>

#include "array.h"

struct record {
/*
	datetime asked;
	time time_to_answer;
	int success;
*/
};

struct entry {
	char *headword;
	/* enum word_type type; */

	struct array definitions;
};

struct dictionary {
	struct array entries;
};

struct definition_position {
	size_t entry_index;
	size_t definition_index;
};

/* TODO: rename, questionnaire, question_table etc */
struct quiz {
	struct array positions;
	size_t n_entries;
	
/*
	struct array records;
*/
};

struct session {
	char *config_filename;
	char *data_filename;

	struct dictionary dict;
	struct quiz quest;

	int quiz_options;
	int quiz_questions;
};

/* session.h */

void init_session(struct session *);
void process_args(struct session *, int, char **);
void read_config(struct session *);
void start_session(struct session *);
void ask_questions(struct session *);
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

/* quiz.h */

enum question_type {DEFINITION, WORD};

void build_quiz(struct quiz *, struct dictionary *);
void print_quiz(struct quiz *);
char *find_definition(struct dictionary *, struct definition_position *);
char *find_headword(struct dictionary *, size_t);
size_t which_entry(struct quiz *, uint32_t);
struct definition_position *pick_definition(struct quiz *, size_t);
unsigned generate_question(struct session *, enum question_type, unsigned);

/* parse.h */

enum parsing_state {BETWEEN, HEADWORD, ENTRY};

void parse_file(struct session *);
void process_line(const char *, ssize_t, enum parsing_state *);
int is_definition(const char *);
