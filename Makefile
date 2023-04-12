.SUFFIXES	:	.o .c
CC		=	cc
CFLAGS		=	-Wall -Werror
OBJS		=	main.o session.o parse.o data.o array.o quiz.o

vocabulary-tester	:	$(OBJS)
	cc $(CFLAGS) -o $@ $(.ALLSRC)

$(OBJS)		:	*.h

.c.o		:
	$(CC) $(CFLAGS)	-c $(.IMPSRC)


lines 		: 
	cat *.h *.c | cat -b
