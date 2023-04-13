.SUFFIXES	:	.o .c
CC		=	cc
CFLAGS		=	-Wall -Werror
OBJS		=	main.o session.o parse.o data.o array.o quiz.o

vocabulary-tester	:	$(OBJS)
	cc $(CFLAGS) -o $@ $^

$(OBJS)		:	*.h

%.o		:	%.c
	$(CC) $(CFLAGS) -c $<

lines 		: 
	cat *.h *.c | cat -b
