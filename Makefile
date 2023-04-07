CFLAGS		=	-Wall -Werror

quiz		:	main.o session.o parse.o data.o array.o
	cc $(CFLAGS) -o $@ main.o session.o parse.o data.o array.o

main.o session.o parse.o data.o array.o		:	*.h

main.o		:	main.c
	cc $(CFLAGS) -c main.c


parse.o		:	parse.c
	cc $(CFLAGS) -c parse.c

data.o		:	data.c
	cc $(CFLAGS) -c data.c

session.o	:	session.c
	cc $(CFLAGS) -c session.c

array.o		:	array.c
	cc $(CFLAGS) -c array.c
