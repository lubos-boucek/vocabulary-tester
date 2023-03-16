#include "common.h"

void init_session(struct session *s)
{
	s->config_filename = "config.txt";
	s->data_filename = "learners.en.txt";

	init_dictionary(&s->dict);
}

void process_args(struct session *s, int argc, char **argv)
{

}

void read_config(struct session *s)
{

}

void clear_session(struct session *s)
{
	clear_dictionary(&s->dict);
}
