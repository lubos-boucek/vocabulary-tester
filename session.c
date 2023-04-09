#include <stdio.h>
#include <unistd.h>

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
	init_questionnaire(&s->quest);
}

void
process_args(struct session *s, int argc, char **argv)
{
	int ch;
	char *end;

	while ((ch = getopt(argc, argv, "f:q:o:de")) != -1) {
		switch (ch) {
		case 'f':
			s->data_filename = optarg;
			break;
		case 'q':
			s->quiz_questions = strtoul(optarg, &end, 10);
			break;

		case 'o':
			s->quiz_options = strtoul(optarg, &end, 10);
			break;

		case 'd':

			break;

		case 'e':

			break;
		}
	}

	validate_args(s);

	printf("DEBUG: questions = %lu, options = %lu\n", s->quiz_questions, s->quiz_options);
}

void
validate_args(struct session *s)
{
	if (s->quiz_options < QUIZ_OPTIONS_MIN)
		s->quiz_options = QUIZ_OPTIONS_MIN;
	if (s->quiz_questions < QUIZ_QUESTIONS_MIN)
		s->quiz_questions = QUIZ_QUESTIONS_MIN;
}

void
read_config(struct session *s)
{

}

void
start_session(struct session *s)
{
	build_questionnaire(&s->quest, &s->dict);
	ask_questions(s);
}

void
ask_questions(struct session *s)
{
	unsigned long correct, answer, i, score = 0;

	for (i = 0; i < s->quiz_questions; i++) {
		correct = generate_question(s, arc4random_uniform(2), s->quiz_options);
		printf("Your answer: ");
		scanf("%lu", &answer);
		fflush(stdin);
		if (correct == answer) {
			printf("Correct!\n");
			score++;
		} else {
			printf("Incorrect.\n");
		}
	}

	printf("Your final score is %lu out of %lu.\n", score, i);
}

void
clear_session(struct session *s)
{
	clear_questionnaire(&s->quest);
	clear_dictionary(&s->dict);
}

/* TODO: rework into multiple functions */
unsigned
generate_question(struct session *s, enum question_type type, unsigned n_options)
{
	uint32_t r, correct_position;
	struct magnifier *dp;
	struct entry *e;
	int i;
	size_t entry_index;

	correct_position = arc4random_uniform(n_options);

	if (type == DEFINITION) {
		r = arc4random_uniform(get_length(&s->quest.magnifiers_array));
		dp = get_element(&s->quest.magnifiers_array, r);

		printf("Which word could be defined by the definition `%s`\n", find_definition(&s->dict, dp));

		for (i = 0; i < n_options; i++) {
			if (i == correct_position) {
				r = 0;
				entry_index = dp->entry_index;
			}
			else {
				r = arc4random_uniform(s->quest.entries_count);
				entry_index = which_entry(&s->quest, r); } e = get_element(&s->dict.entries_array, entry_index); printf("\t%d) %s\n", i + 1, e->headword);
		}
	} else if (type == WORD) {
		r = arc4random_uniform(s->quest.entries_count);

		entry_index = which_entry(&s->quest, r);
		printf("Which definition could be used to describe this word: `%s`\n", find_headword(&s->dict, entry_index)); 

		for (i = 0; i < n_options; i++) {
			if (i == correct_position) {
				dp = pick_definition(&s->quest, entry_index);
			} else {
				r = arc4random_uniform(get_length(&s->quest.magnifiers_array));
				dp = get_element(&s->quest.magnifiers_array, r);
			}

			printf("\t%d) %s\n", i + 1, find_definition(&s->dict, dp));
		}
	}

	return correct_position + 1;
}
