sinclude Makefile.common

vocabulary-tester	:	$(OBJS)
	cc $(CFLAGS) -o $@ $^

$(OBJS)		:	*.h

%.o		:	%.c
	$(CC) $(CFLAGS) -c $<

lines 		: 
	cat *.h *.c | cat -b
