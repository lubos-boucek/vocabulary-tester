#include <stdio.h>

#include "common.h"

int
main(int argc, char **argv)
{
	struct session this_session;

	init_session(&this_session);
	process_args(&this_session, argc, argv);
	read_config(&this_session);
	parse_file(&this_session);

	start_session(&this_session);

	clear_session(&this_session);

	return 0;
}
