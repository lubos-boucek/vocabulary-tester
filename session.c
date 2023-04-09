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

	/* TODO: init_quiz */
	s->quest.n_entries = 0;
	new_array(&s->quest.positions, sizeof(struct definition_position));
}

void
process_args(struct session *s, int argc, char **argv)
{
	int ch;

	while ((ch = getopt(argc, argv, "f:q:o:de")) != -1) {
		switch (ch) {
		case 'f':
			s->data_filename = optarg;
			break;
		case 'q':
			/* strtoul */		
			break;

		case 'o':

			break;

		case 'd':

			break;

		case 'e':

			break;
		}
	}
}

void
read_config(struct session *s)
{

}

void
start_session(struct session *s)
{
	build_quiz(&s->quest, &s->dict);
	ask_questions(s);
}

void
ask_questions(struct session *s)
{
	unsigned correct, answer;
	int i;

	for (i = 0; i < s->quiz_questions; i++) {
		correct = generate_question(s, arc4random_uniform(2), s->quiz_options);
		printf("Your answer: ");
		scanf("%u", &answer);
		fflush(stdin);
		if (correct == answer) {
			printf("Correct!\n");
		} else {
			printf("Incorrect.\n");
		}
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
