#include "common.h"
#include "defaults.h"

void
init_session(struct session *s)
{
	s->config_filename = "config.txt";
	s->data_filename = "learners.en.txt";
/* default */
	s->quiz_options = QUIZ_OPTIONS;
	s->quiz_questions = QUIZ_QUESTIONS;

	init_dictionary(&s->dict);

	/* TODO: init_quiz */
	s->quest.n_entries = 0;
	new_array(&s->quest.positions, sizeof(struct definition_position));
}

void
process_args(struct session *s, int argc, char **argv)
{

}

void
read_config(struct session *s)
{

}

void
start_session(struct session *s)
{
	int i;

	build_quiz(&s->quest, &s->dict);
	print_dictionary(&s->dict);
	print_quiz(&s->quest);

	for (i = 0; i < s->quiz_questions; i++) {
		generate_question(s, DEFINITION, s->quiz_options);
	}
	for (i = 0; i < s->quiz_questions; i++) {
		generate_question(s, WORD, s->quiz_options);
	}
}

void
clear_session(struct session *s)
{
	/* TODO: clear_quiz */
	delete_array(&s->quest.positions);
	s->quest.n_entries = 0;

	clear_dictionary(&s->dict);
}
