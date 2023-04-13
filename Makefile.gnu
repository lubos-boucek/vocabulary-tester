sinclude Makefile.common

OBJS += compat/strlcpy.o

vocabulary-tester	:	$(OBJS)
	cc $(CFLAGS) -o $@ $^

$(OBJS)		:	*.h compat/*.h

%.o		:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clear		:
	rm $(OBJS)

lines 		: 
	cat *.h *.c | cat -b
